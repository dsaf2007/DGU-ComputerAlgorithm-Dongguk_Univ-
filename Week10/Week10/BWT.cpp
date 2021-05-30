//2016112154 정동구
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
	for (int j = 0; j < length; j++)//한칸씩 밀어서 생성한 문자열을 rest에 pushback한다.
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
	std::sort(rest.begin(), rest.end());//사전순 정렬
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
	for (int i = 0; i < length;)//첫번째 rest를 통해 중복되어있는 문자의 순서를 매긴다. pair을 이용하고 이를 first_tuples에 push back 한다.
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
			char_set.push_back(tuple);//마지막 rest도 순서를 매기기 위해 만든 char_set에 tuple push_back
			i++;
		}
		else
		{
			j += num;
			tuple = first[j];
			num = 0;
		}
	}
	
	for (int i = 0; i < char_set.size(); i++)//char_set에 있는 문자를 기준으로 순서대로 세어서 번호를 매긴다.
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

}


void BWT::decode()//문자열 복원.
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