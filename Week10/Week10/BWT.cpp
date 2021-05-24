#include "BWT.h"


BWT::BWT(std::string input)
{
	this->pattern_str = input;
}

BWT::~BWT()
{

}

void BWT::init()
{
	int length = pattern_str.length()+1;
	pattern_str += "$";
	std::string temp = pattern_str;
	for (int j = 0; j < length; j++)
	{
		rest.push_back(pattern_str);
		for (int i = 0; i < length; i++)
		{
			pattern_str[i] = temp[(i + 1) % length];
		}
		temp = pattern_str;
	}
}