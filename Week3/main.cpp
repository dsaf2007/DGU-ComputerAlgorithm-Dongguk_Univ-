#include <iostream>
#include <string>
#include "heap.h"
#include "merge.h"
void exec_heap();
void exec_merge();

int main()
{
	exec_merge();
}

void exec_heap()
{
	int n;
	Heap heap;
	int arr[10];

	for (int i = 0; i < 10; i++)
	{
		std::cin >> n;
		heap.insert(n);
	}
	for (int i = 0; i < 10; i++)
	{
		arr[i] = heap.removeMax();
	}
	for (int i = 0; i < 10; i++)
	{
		std::cout << arr[i] << " ";
	}std::cout << "\n";
}

void exec_merge()
{
	int in;
	std::string input_str;
	std::vector<int> input;
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
	//m.mergeSort(0,input.size()-1);
	m.nonRecMergeSort();
	m.printArr();
}