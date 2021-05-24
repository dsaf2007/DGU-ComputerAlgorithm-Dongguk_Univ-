#include <iostream>
#include <vector>
#include <cstdlib>


class BWT
{
public:
	BWT(std::string input);//constructor
	~BWT();//destructor

	void init();	
private:
	std::string pattern_str;
	std::vector<std::vector<std::string>> rest;
};