#include "ACTG.h"


ACTG::ACTG()
{
	for (int i = 0; i < 1000000; i++)
	{
		ref_DNA_seq += random();
	}
}

ACTG::~ACTG(){}

void ACTG::init()
{

}

char ACTG::random()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 3);

	return actg[dis(gen)];
}

