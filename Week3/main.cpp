//2016112154 ������
#include <iostream>
#include <string>
#include "heap.h"//�� ������ ���� class�� �����ϴ� ���
#include "merge.h"//�պ������� �ϱ� ���� class�� �����ϴ� ���
void exec_heap();//�� ����
void exec_merge1();//��� �պ�
void exec_merge2();//����� �պ�

int main()
{
	exec_heap();
}

void exec_heap()
{
	int n;
	Heap heap;
	int arr[10];
	std::cout << "�迭�� �Է��Ͻÿ� : ";
	for (int i = 0; i < 10; i++)
	{
		std::cin >> n;
		heap.insert(n);
	}
	std::cout << "������ �� : ";
	for (int i = 1; i < 11; i++)
	{
		std::cout<<heap.element[i]<<" ";
	}std::cout << "\n";
	std::cout << " �� ���� ��� : ";
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
	std::cout << "�迭�� �Է��Ͻÿ� : \n";
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
	m.mergeSort(0,input.size()-1);

	m.printArr();
}

void exec_merge2()
{
	int in;
	std::string input_str;
	std::vector<int> input;
	std::cout << "�迭�� �Է��Ͻÿ� : \n";
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
	m.nonRecMergeSort(0, input.size() - 1);
	m.printArr();
}