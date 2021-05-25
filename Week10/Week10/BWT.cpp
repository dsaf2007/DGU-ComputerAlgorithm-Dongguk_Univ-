//2016112154 Á¤µ¿±¸
#include "BWT.h"


BWT::BWT(std::string input)
{
	this->pattern_str = input;
	this->pattern_str += "$";
}

BWT::~BWT()
{

}

void BWT::init()
{
	int length = pattern_str.length();
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

void BWT::sortRest()
{
	//for (int i = 0; i < pattern_str.length()-1; i++)
	//{
	//	for (int j = 0; j < rest[i].length(); j++)
	//	{
	//		if ((int)rest[i][j] == (int)rest[i + 1][j])
	//			continue;
	//		else if ((int)rest[i][j] > (int)rest[i + 1][j])
	//		{
	//			std::string temp = rest[i + 1];
	//			rest[i + 1] = rest[i];
	//			rest[i] = temp;
	//			break;
	//		}
	//		else
	//			break;

	//	}
	//}
	std::sort(rest.begin(), rest.end());
}

void BWT::getResult()
{
	for (int i = 0; i < rest.size(); i++)
	{
		result_str += rest[i][rest[i].length()-1];
	}

	std::cout << "result string is : " << result_str << std::endl;
}