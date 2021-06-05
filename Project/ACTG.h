#include <iostream>
#include <random>
#include <ctime>
#include <fstream>

class ACTG
{
public:
	ACTG(int k_,int n_);
	~ACTG();

	void init();
	char random();
	void restore();
	void compare(double time);
	void makeText();
	void printSizeInfo();
	void BMRestore(int x);
	void execute();

private:
	std::string ref_DNA_seq;
	std::string my_DNA_seq;
	std::string restore_seq;
	std::string actg = "ACTG";
	int k;
	int M;
	int N;
	std::vector<std::string> short_read;
};