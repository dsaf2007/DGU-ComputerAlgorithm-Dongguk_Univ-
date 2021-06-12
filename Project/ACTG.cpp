#pragma once
#include "ACTG.h"
#include "BoyerMoor.h"
#include <time.h>

ACTG::ACTG(std::string my, std::string ref,std::vector<std::string> short_read_,std::string path_)//생성자
{
	my_DNA_seq = my;
	ref_DNA_seq = ref;
	short_read.resize(short_read_.size());
	std::copy(short_read_.begin(), short_read_.end(), short_read.begin());
	path = path_;

	N = my_DNA_seq.length();
	L = short_read[0].length();
	M = short_read.size();
	
	miss = 0;
	for (int i = 0; i < N; i++)
	{
		restore_seq += " ";
	}

}

ACTG::~ACTG(){}

void ACTG::initMyDNA(int x)//read 길이 마다 0~2개 만큼의 문자 변경
{
	for (int i = (x)*(my_DNA_seq.length()/20); i < ((x+1) * (my_DNA_seq.length() / 20))-L; i += L)
	{
		my_DNA_seq[i + rand() % L] = random();
		my_DNA_seq[i + rand() % L] = random();
	}	
}

void ACTG::exec_initMyDNA()//멀티스레딩
{
	std::vector<std::thread> My;

	for (int i = 0; i < 20; i++)
	{
		My.emplace_back(std::thread(&ACTG::initMyDNA, this, i));
	}
	for (auto& init : My)
		init.join();
}

void ACTG::makeShortread()//short read 생성
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, my_DNA_seq.length() - L - 1);
	std::mutex g_lock;

	for (int i = dis(gen); i < my_DNA_seq.length(); i = dis(gen))
	{
		std::string read_str = "";
		for (int j = 0; j < L; j++)
		{
			read_str += my_DNA_seq[i + j];
		}
		short_read.push_back(read_str);
		if (short_read.size() == M)
			break;
	}
}

char ACTG::random()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 3);

	return actg[dis(gen)];
}


void ACTG::restore(int x)//DNA restore with trivial method
{
	int mismatch;
	for (int i = (x) * (M / 20); i < (x + 1) * (M / 20); i++)
	{
		for (int j = 0; j < N; j++)
		{
			mismatch = 0;
			for (int x = 0; x < L; x++)
			{
				if (short_read[i][x] != ref_DNA_seq[j + x])
					mismatch++;
				if (mismatch >= 4)//4개의 missmatch 허용
					break;
				if ((x == L - 1) && mismatch < 4)
				{
					for (int y = 0; y < L; y++)
					{
						restore_seq[j + y] = short_read[i][y];
					}
				}
			}
		}
	}
}

void ACTG::execute_triv()//trivial method multi threading
{
	std::cout << short_read.size() << std::endl;
	start = time(NULL);
	for (int i = 0; i < 20; i++)
	{
		threads.emplace_back(std::thread(&ACTG::restore, this, i));
	}
	for (auto& thread : threads)
		thread.join();
	end = time(NULL);

	elapse_time = (double)(end - start);
}

void ACTG::BMRestore(int x)//Boyer-Moor를 이용한 DNA 복원
{
	for(int i = (x) * (M / 20); i < (x+1)*(M/20) ; i++)
	{
		std::vector<int> bad_table = makeBad_table(short_read[i]);
		std::vector<int> suffix_table = makeGoddsuffix_table(short_read[i]);
		int index = search(bad_table, suffix_table, ref_DNA_seq, short_read[i]);
		if (index > -1)
		{
			for (int j = 0; j < short_read[i].length(); j++)
			{
				restore_seq[index + j] = short_read[i][j];
			}
		}
	}
}

void ACTG::execute()//BMRestore multi threading
{
	std::cout << short_read.size() << std::endl;
	start = time(NULL);
	for (int i = 0; i < 20; i++)
	{
		threads.emplace_back(std::thread(&ACTG::BMRestore, this, i));
	}
	for (auto& thread : threads)
		thread.join();
	end = time(NULL);

	elapse_time = (double)(end - start);
}

void ACTG::compare(int x)//my dna와 resotre dna 비교
{
	for (int i = 0; i < N; i++)
	{
		if (restore_seq[i] != my_DNA_seq[i])
		{
			miss++;
		}
	}
}

//void ACTG::exec_compare()//compare 함수 multi threading
//{
//	std::vector<std::thread> comp;
//
//	for (int i = 0; i < 20; i++)
//	{
//		comp.emplace_back(std::thread(&ACTG::compare, this, i));
//	}
//	for (auto& compare : comp)
//		compare.join();
//}

void ACTG::makeText()//결과 텍스트 출력
{

	std::ofstream writeResult(path+"result.txt");
	writeResult << "N :" << N << ",M : " << M << ",K : " << L <<", d: 4"<<"\n";
	writeResult << "소요 시간 : " << elapse_time<<"\n";
	writeResult << "일치율 : " << ((double)((N - miss) / (double)N)) * 100 << "%\n";
	writeResult << "불일치 문자 개수 : " << miss << std::endl;

	std::ofstream restore(path+"restore_seq.txt");

	restore << restore_seq;
}

void ACTG::printSizeInfo()
{
	std::cout << "number of short read : " << M << std::endl << "length of short read : " << L << std::endl;
}