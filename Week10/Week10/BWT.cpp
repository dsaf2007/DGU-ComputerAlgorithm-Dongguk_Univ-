//2016112154 ������
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
	for (int j = 0; j < length; j++)//��ĭ�� �о ������ ���ڿ��� rest�� pushback�Ѵ�.
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
	std::sort(rest.begin(), rest.end());//������ ����
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
	for (int i = 0; i < length;)//ù��° rest�� ���� �ߺ��Ǿ��ִ� ������ ������ �ű��. pair�� �̿��ϰ� �̸� first_tuples�� push back �Ѵ�.
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
			char_set.push_back(tuple);//������ rest�� ������ �ű�� ���� ���� char_set�� tuple push_back
			i++;
		}
		else
		{
			j += num;
			tuple = first[j];
			num = 0;
		}
	}
	
	for (int i = 0; i < char_set.size(); i++)//char_set�� �ִ� ���ڸ� �������� ������� ��� ��ȣ�� �ű��.
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


void BWT::decode()//���ڿ� ����.
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