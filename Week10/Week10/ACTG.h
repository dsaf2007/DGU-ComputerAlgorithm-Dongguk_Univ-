#include <iostream>
#include <random>
#include <ctime>


class ACTG
{
public:
	ACTG();
	~ACTG();

	void init();
	char random();

private:
	std::string ref_DNA_seq;
	std::string actg = "ACTG";
};