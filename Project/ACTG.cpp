#pragma once
#include "ACTG.h"
#include "BoyerMoor.h"
#include <mutex>
#include <thread>
#include <future>
ACTG::ACTG(int k_,int m_)//생성자
{
	M = m_;
	k = k_;
	N = 1000000;
	for (int i = 0; i < N; i++)
	{
		ref_DNA_seq += random();
	}
	my_DNA_seq = ref_DNA_seq;
}

ACTG::~ACTG(){}

void ACTG::init()//short read를 생성한다.
{
	for (int i = 0; i < my_DNA_seq.length(); i += k)
	{
		my_DNA_seq[i + rand() % k] = random();
		my_DNA_seq[i + rand() % k] = random();
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, my_DNA_seq.length()-k-1);
	
	for (int i = dis(gen); i < my_DNA_seq.length(); i = dis(gen))
	{
		std::string read_str = "";
		for (int j = 0; j < k; j++)
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


void ACTG::restore()
{
	restore_seq = ref_DNA_seq;
	int mismatch;
	for (int i = 0; i < short_read.size(); i++)
	{
		for (int j = 0; j < N; j++)
		{
			mismatch = 0;
			for (int x = 0; x < k; x++)
			{
				if (short_read[i][x] != ref_DNA_seq[j + x])
					mismatch++;
				if (mismatch >= 2)
					break;
				if ((x == k - 1) && mismatch < 2)
				{
					for (int y = 0; y < k; y++)
					{
						restore_seq[j + y] = short_read[i][y];
					}
				}
			}
		}
	}
}

void ACTG::BMRestore(int x)
{
	restore_seq = ref_DNA_seq;
	int size = short_read.size();
	std::cout << size<<" "<<x;
	std::mutex g_lock;
	for(int i = x*(size/4); i < (x+1)*(size/4) ; i++)
	{
		std::vector<int> bad_table = makeBad_table(short_read[i]);
		std::vector<int> suffix_table = makeGoddsuffix_table(short_read[i]);
		int index = search(bad_table, suffix_table, restore_seq, short_read[i]);
		if (index > -1)
		{
		//std::lock_guard<std::mutex>lock_guard(g_lock);
			for (int j = 0; j < short_read[i].length(); j++)
			{
				restore_seq[index + j] = short_read[i][j];
			}
		}
	}
}

void ACTG::execute()
{
	//std::vector<std::thread> threads;
	//for (int i = 0; i < 4; i++)
	//{
	//	//threads.emplace_back(std::thread(&ACTG::BMRestore, this, i));
	//
	//}

	auto t1 = std::async(&ACTG::BMRestore, this, 0);
	auto t2 = std::async(&ACTG::BMRestore, this, 1);
	auto t3 = std::async(&ACTG::BMRestore, this, 2);
	auto t4 = std::async(&ACTG::BMRestore, this, 3);
	/*for (auto& thread : threads)
		thread.join();*/

}

void ACTG::compare(double time)
{
	int miss = 0;
	for (int i = 0; i < N; i++)
	{
		if (restore_seq[i] != my_DNA_seq[i])
		{
			miss++;
		}
		
	}
	std::ofstream writeResult("result.txt");
	writeResult << "소요 시간 : " << time;
	writeResult << "일치율 : " << ((double)(N -miss) / (double)N) * 100 << "%\n";
	writeResult << "불일치 문자 개수 : " << miss << std::endl;
}


void ACTG::makeText()
{
	std::ofstream writeShortRead("short_read.txt");
	std::ofstream myDNA("my_DNA.txt");
	std::ofstream restore("restore_seq.txt");
	for (int i = 0; i < short_read.size(); i++)
	{
		writeShortRead << short_read[i]<<"\n";
	}
	myDNA << my_DNA_seq;
	restore << restore_seq;
}

void ACTG::printSizeInfo()
{
	std::cout << "number of short read : " << M << std::endl << "length of short read : " << k << std::endl;
}