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
	int length = rest[0].length();
	std::sort(rest.begin(), rest.end());
	for (int i = 0; i < length; i++)
	{
		first += rest[i][0];
		last += rest[i][rest[i].length() - 1];
	}
	std::cout <<"first: " <<first << std::endl << "last: "<<last << std::endl;
	last_tuples.resize(length);
	std::vector<char> char_set;

	char tuple = first[0];
	int num = 0;
	int j = 0;
	for (int i = 0; i < length;)
	{
		if (tuple == '$')
		{
			first_tuples.push_back(std::pair<char, int>(tuple, num));
			char_set.push_back(tuple);
			tuple = first[i + 1];
			j = i + 1;
			i++;
			
			continue;
		}
		if (first[i] == tuple)
		{
			num++;
			first_tuples.push_back(std::pair<char, int>(tuple, num));
			char_set.push_back(tuple);
			i++;
		}
		else
		{
			j += num;
			tuple = first[j];
			num = 0;
		}
	}
	
	for (int i = 0; i < char_set.size(); i++)
	{
		int x = 0;
		for (int j = 0; j < length; j++)
		{
			if (char_set[i] == last[j])
			{
				x++;
				last_tuples[j]=(std::pair<char, int>(char_set[i], x));
			}
		}
	}
	/*for (int i = 0; i < length; i++)
	{
		std::cout << first_tuples[i].first << " " << first_tuples[i].second << std::endl;
	}*/

	/*for (int i = 0; i < length; i++)
	{
		std::cout << last_tuples[i].first << " " << last_tuples[i].second << std::endl;
	}*/
}

//void BWT::getResult()
//{
//	for (int i = 0; i < rest.size(); i++)
//	{
//		result_str += rest[i][rest[i].length()-1];
//	}
//
//	std::cout << "result string is : " << result_str << std::endl;
//}

void BWT::decode()
{
	int length = 0;
	int index = 0;
	result_str += last_tuples[0].first;
	while (result_str.length()< pattern_str.length()-1)
	{
		for (int i = 0; i < pattern_str.length(); i++)
		{
			if (first_tuples[i] == last_tuples[index])
			{
				
				index = i;
				if (last_tuples[index].first == '$')continue;
				result_str += last_tuples[index].first;
			}
		}
	}
	std::reverse(result_str.begin(), result_str.end());
	std::cout << result_str << std::endl;
}