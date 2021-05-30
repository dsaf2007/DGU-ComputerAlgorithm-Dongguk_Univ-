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
	void decode();
private:
	std::string pattern_str="$";
	std::vector<std::string> rest;
	std::string result_str="";
	std::string first = "";
	std::string last = "";
	std::vector<std::pair<char, int>> first_tuples;
	std::vector<std::pair<char, int>> last_tuples;
};