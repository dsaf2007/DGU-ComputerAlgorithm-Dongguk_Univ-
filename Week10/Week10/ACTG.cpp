#include "ACTG.h"


ACTG::ACTG(int k_,int n_)
{
	n = n_;
	k = k_;
	for (int i = 0; i < 1000000; i++)
	{
		ref_DNA_seq += random();
	}
	my_DNA_seq = ref_DNA_seq;
}

ACTG::~ACTG(){}

void ACTG::init()
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
		if (short_read.size() == n)
			break;
	}
	std::cout << short_read.size();
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

}
