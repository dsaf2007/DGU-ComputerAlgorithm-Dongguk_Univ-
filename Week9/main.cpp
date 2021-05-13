//2016112154 ������
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <random>
#include <chrono>
void bruteForce(std::string text, std::string pattern_,std::string output);
void RabinKarp(std::string text, std::string pattern, std::string output);
void Kmp(std::string text, std::string pattern_, std::string output);
void InitSP(std::string pattern_, int m);

int* SP;

int charToInt(char c) {
	return (int)(c - '0');
}

int main()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 3);
	std::string ATGC[4] = { "A","T","G","C" };
	/*std::ofstream writeFile("text_4.txt");
	for (int i = 0; i < 10000000; i++)
	{
		writeFile << ATGC[dis(gen)];
	}*/
	std::ofstream time_output("time14.txt");

	std::ifstream readFile("text_4.txt");
	std::string plain_text;
	std::getline(readFile, plain_text);

	//std::string pattern = "CTGAT";
	std::string pattern;
	for (int i = 0; i < 10; i++)
	{
		pattern += ATGC[(dis(gen))];
	}
	SP = new int[pattern.length()];
	std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();
	bruteForce(plain_text, pattern, "brute_result14.txt");
	std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();
	std::chrono::microseconds micro = std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);
	time_output << "bruteForce �ҿ�ð� : " << micro.count() << " microseconds" << std::endl;

	StartTime = std::chrono::system_clock::now();
	RabinKarp(plain_text, pattern, "RK_result14.txt");
 EndTime = std::chrono::system_clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);
	time_output << "RabinKarp �ҿ�ð� : " << micro.count() << " microseconds" << std::endl;

	StartTime = std::chrono::system_clock::now();
	Kmp(plain_text, pattern,"Kmp_result14.txt");
	EndTime = std::chrono::system_clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);
	time_output << "Kmp �ҿ�ð� : " << micro.count() << " microseconds" << std::endl;
}


void bruteForce(std::string text, std::string pattern_,std::string output)
{
	std::ofstream writeFile(output);
	int num = 0;
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


void RabinKarp(std::string text, std::string pattern_, std::string output)
{
	std::ofstream writeFile(output);
	int rkCount = 0;
	const int d = 4;
	const int q = 524287;
	int m = pattern_.length();
	int n = text.length();
	int i, j, dM = 1, h1 = 0, h2 = 0;
	bool flag = false;
	for (i = 1; i < m; i++) dM = (d * dM) % q;
	for (i = 0; i < m; i++) {//�ؽ�
		h1 = (h1 * d + charToInt(pattern_[i])) % q;
		h2 = (h2 * d + charToInt(text[i])) % q;
	}
	for (i = 0; i < n - m + 1; i++) 
	{
		if (h1 == h2) {//�ؽ� ���� ������ ��� �ؽ�Ʈ ��ġ
			flag = true;
			for (j = i; j < m + i; j++)
				if (text[j] != pattern_[j - i]) 
				{
					flag = false;
					break;
				}
		}
		if (flag)
		{
			writeFile << i + 1 << "��° ��ġ����"<< pattern_<<" �߰�\n";
			rkCount++;
		}
		if (i < n - m) 
		{
			h2 = (h2 - charToInt(text[i]) * dM) % q;
			h2 = (h2 * d + charToInt(text[i + m])) % q;
			flag = false;
		}
	}
	writeFile <<"�� " << rkCount <<"���� ���� �߰�\n";
}

void InitSP(std::string pattern_,int m) //�ִ� ���κ� ���̺�
{
	int i, j;
	SP[0] = -1;
	for (i = 1, j = -1; i <= m - 1; i++) {
		while ((j >= 0) && (pattern_[j + 1] != pattern_[i]))
		{
			j = SP[j];
		}
		if (pattern_[j + 1] == pattern_[i]) 
			j++;
		SP[i] = j;
	}
}

void Kmp(std::string text, std::string pattern_, std::string output)
{
	std::ofstream writeFile(output);
	int kmpCount = 0;
	int i, j;
	int m = pattern_.length();
	int n = text.length();
	InitSP(pattern_, m);
	for (i = 0, j = -1; i <= n - 1; i++)
	{
		while ((j >= 0) && (pattern_[j + 1] != text[i])) 
		{
			j = SP[j];
		}
		if (pattern_[j + 1] == text[i])
		{
			j++;
		}
		if (j == m - 1) {
			writeFile << i - j + 1 << "��° ��ġ���� "<<pattern_ << " �߰�\n";
			j = SP[j];
			kmpCount++;
		}
	}
	writeFile << "�� " << kmpCount << "���� ���� �߰�\n";
}