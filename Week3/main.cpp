//2016112154 정동구
#include <iostream>
#include <string>
#include "heap.h"//힙 생성을 위한 class를 포함하는 헤더
#include "merge.h"//합병정렬을 하기 위한 class를 포함하는 헤더
void exec_heap();//힙 정렬
void exec_merge1();//재귀 합병
void exec_merge2();//비재귀 합병

int main()
{
	exec_heap();
}

void exec_heap()
{
	int n;
	Heap heap;
	int arr[10];
	std::cout << "배열을 입력하시오 : ";
	for (int i = 0; i < 10; i++)
	{
		std::cin >> n;
		heap.insert(n);
	}
	std::cout << "생성된 힙 : ";
	for (int i = 1; i < 11; i++)
	{
		std::cout<<heap.element[i]<<" ";
	}std::cout << "\n";
	std::cout << " 힙 정렬 결과 : ";
	for (int i = 0; i < 10; i++)
	{
		arr[i] = heap.removeMin();
	}
	for (int i = 0; i < 10; i++)
	{
		std::cout << arr[i] << " ";
	}std::cout << "\n";
}

void exec_merge1()
{
	int in;
	std::string input_str;
	std::vector<int> input;
	std::cout << "배열을 입력하시오 : \n";
	std::getline(std::cin, input_str);
	std::string strNum = ""; // 각각의 숫자를 저장할 임시 String
	for (int i = 0; i < input_str.length(); i++)
	{
		if (input_str.at(i) == ' ')
		{
			// 현재까지 저장한 문자(숫자)들을 Vector에 추가 후 String 초기화
			input.push_back(atoi(strNum.c_str()));
			strNum = "";
		}
		else
		{
			// 띄어쓰기가 나올 때까지 문자 더함
			strNum += input_str.at(i);
			continue;
		}
	}
	input.push_back(atoi(strNum.c_str())); // 마지막 숫자도 벡터에 추가

	
	Merge m(input);
	m.mergeSort(0,input.size()-1);

	m.printArr();
}

void exec_merge2()
{
	int in;
	std::string input_str;
	std::vector<int> input;
	std::cout << "배열을 입력하시오 : \n";
	std::getline(std::cin, input_str);
	std::string strNum = ""; // 각각의 숫자를 저장할 임시 String
	for (int i = 0; i < input_str.length(); i++)
	{
		if (input_str.at(i) == ' ')
		{
			// 현재까지 저장한 문자(숫자)들을 Vector에 추가 후 String 초기화
			input.push_back(atoi(strNum.c_str()));
			strNum = "";
		}
		else
		{
			// 띄어쓰기가 나올 때까지 문자 더함
			strNum += input_str.at(i);
			continue;
		}
	}
	input.push_back(atoi(strNum.c_str())); // 마지막 숫자도 벡터에 추가


	Merge m(input);
	m.nonRecMergeSort(0, input.size() - 1);
	m.printArr();
}