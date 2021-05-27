#include <iostream>
#include <random>
#include <ctime>


class ACTG
{
public:
	ACTG(int k_,int n_);
	~ACTG();

	void init();
	char random();
	void restore();

private:
	std::string ref_DNA_seq;
	std::string my_DNA_seq;
	std::string actg = "ACTG";
	int k;
	int n;
	std::vector<std::string> short_read;
};