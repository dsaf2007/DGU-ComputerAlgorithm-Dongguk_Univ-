//2016112154 ������
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <random>

void bruteForce(std::string text, std::string pattern_);

int main()
{
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 9);
	std::ofstream writeFile("text_4.txt");
	for (int i = 0; i < 10000000; i++)
	{
		writeFile << dis(gen);
	}
	
	std::ifstream readFile("text_4.txt");
	std::string plain_text;
	std::getline(readFile, plain_text);

	std::string pattern = "";

	for (int i = 0; i < 5; i++)
	{
		pattern += std::to_string(dis(gen));
	}
	bruteForce(plain_text, pattern);
}


void bruteForce(std::string text, std::string pattern_)
{
	std::ofstream writeFile("result5_4.txt");
	int num = 0;
	writeFile << "pattern : " << pattern_<<"\n";
	for (int i = 0; i < text.length(); i++)
	{
		for (int j = 0; j < pattern_.length(); j++)
		{
			if (text[i + j] != pattern_[j])
				break;

			if (j == pattern_.length() - 1)
			{
				writeFile << i + 1 << "��° ��ġ���� " << pattern_ << "�߰�\n";
				num++;
			}
		}
	}
	writeFile << "\n�� " << num << "���� pattern ��ġ\n";
	return;
}
