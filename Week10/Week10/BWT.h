//2016112154 Á¤µ¿±¸
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

class BWT
{
public:
	BWT(std::string input);//constructor
	~BWT();//destructor

	void init();
	void sortRest();
	void getResult();
private:
	std::string pattern_str="$";
	std::vector<std::string> rest;
	std::string result_str="";
};