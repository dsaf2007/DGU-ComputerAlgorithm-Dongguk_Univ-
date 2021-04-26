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
	/*std::ofstream writeFile("text_1.txt");
	for (int i = 0; i < 10000; i++)
	{
		writeFile << dis(gen);
	}*/
	
	std::ifstream readFile("text_1.txt");
	std::string plain_text;
	std::getline(readFile, plain_text);

	std::string pattern = "";

	for (int i = 0; i < 4; i++)
	{
		pattern += std::to_string(dis(gen));
	}
	bruteForce(plain_text, "57147");
}


void bruteForce(std::string text, std::string pattern_)
{
	std::ofstream writeFile("result.txt");
	int num = 0;
	for (int i = 0; i < text.length(); i++)
	{
		for (int j = 0; j < pattern_.length(); j++)
		{
			if (text[i + j] != pattern_[j])
				break;

			if (j == pattern_.length() - 1)
			{
				writeFile << i + 1 << "번째 위치에서 " << pattern_ << "발견\n";
				num++;
			}
		}
	}
	writeFile << "\n총 " << num << "개의 pattern 일치\n";
	return;
}
