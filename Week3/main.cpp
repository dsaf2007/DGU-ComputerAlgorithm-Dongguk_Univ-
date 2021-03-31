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
	std::string strNum = ""; // ������ ���ڸ� ������ �ӽ� String
	for (int i = 0; i < input_str.length(); i++)
	{
		if (input_str.at(i) == ' ')
		{
			// ������� ������ ����(����)���� Vector�� �߰� �� String �ʱ�ȭ
			input.push_back(atoi(strNum.c_str()));
			strNum = "";
		}
		else
		{
			// ���Ⱑ ���� ������ ���� ����
			strNum += input_str.at(i);
			continue;
		}
	}
	input.push_back(atoi(strNum.c_str())); // ������ ���ڵ� ���Ϳ� �߰�

	
	Merge m(input);
	//m.mergeSort(0,input.size()-1);
	m.nonRecMergeSort();
	m.printArr();
}