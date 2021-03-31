//2016112154 ������
#pragma once
#include <vector>

class Merge
{
public:
	Merge(std::vector<int> input)//������
	{
		size = input.size();//�迭 ũ��
		arr = new int[size];//�迭
		sorted_arr = new int[size];//���Ŀ� �̿��� �迭
		for (int i = 0; i < size; i++)
		{
			arr[i] = input[i];//�迭 �ʱ�ȭ
		}
	}
	~Merge()//�Ҹ���
	{
		delete[] arr;
		delete[] sorted_arr;
	}
	void merge(int start, int mid, int end)//����պ��Լ�
	{
		
		int i = start, j = mid + 1, k = start;
		//���� ���ĵ� ����Ʈ �պ�
		while (i <= mid && j <= end)
		{
			if (arr[i] <= arr[j])
			{
				sorted_arr[k] = arr[i];
				i++;
			}
			else//arr[i] > arr[j]
			{
				sorted_arr[k] = arr[j];
				j++;
			}
			k++;

		}
		//�����ִ� ���� �ϰ� ����
		if (i > mid)
		{
			for (int x = j; x <= end; x++)
			{
				sorted_arr[k] = arr[x];
				k++;
			}
		}
		else//�����ִ� ���� �ϰ� ����
		{
			for (int x = i; x <= mid; x++)
			{
				sorted_arr[k] = arr[x];
				k++;
			}
		}
		PrintSpace(start);
		std::cout << "[";//���ҵ� �κе� ǥ��.
		for (int x = start; x < k; x++)
		{
			std::cout << sorted_arr[x] << " ";
		}std::cout << "]\n";
		for (int x = start; x <= end; x++)//�ӽù迭�� ����Ʈ�� �迭�� ����
		{
			arr[x] = sorted_arr[x];
		}

	}
	void nonRecMerge(int start, int mid, int end)//����� �պ��Լ�. �պ��Լ��� ����. ���Һκ� ǥ�ð� ����� ���� �ʾ� �� �κи� ������ + �������� ���� ����� ���� vector�� pushback
	{
		int* proc = new int[size];
		int i = start, j = mid + 1, k = start;

		while (i <= mid && j <= end)
		{
			if (arr[i] <= arr[j])
			{
				sorted_arr[k] = arr[i];
				i++;
			}
			else//arr[i] > arr[j]
			{
				sorted_arr[k] = arr[j];
				j++;
			}
			k++;

		}
		if (i > mid)
		{
			for (int x = j; x <= end; x++)
			{
				sorted_arr[k] = arr[x];
				k++;
			}
		}
		else
		{
			for (int x = i; x <= mid; x++)
			{
				sorted_arr[k] = arr[x];
				k++;
			}
		}
		for (int x = start; x <= end; x++)
		{
			arr[x] = sorted_arr[x];
		}
		for (int x = 0; x < size; x++)
		{
			proc[x] = arr[x];
		}
		process_arr.push_back(proc);//���� ���� ����
	
	}
	void mergeSort(int start, int end)//��� �պ� ����
	{
		int* proc = new int[size];
		if (start < end)
		{
			int mid = (start + end) / 2;

			mergeSort(start, mid);//left
			mergeSort(mid + 1, end);//right
			merge(start, mid, end);//�պ�
			for (int i = 0; i < size; i++)//������ vector�� ����.
			{
				proc[i] = arr[i];
			}
			process_arr.push_back(proc);


		}
	}

	void nonRecMergeSort(int start,int end)//����� �պ� ����
	{
		int left, right,mid;
		//m �������� ������� ����Ʈ ����
		for (int m = 1; m <=end; m = 2 * m)
		{
			for (int i = 0; i < end; i += 2 * m)
			{
				left = i;
				mid = i + m - 1;
				right = min(i + 2 * m - 1, end);

				nonRecMerge(left,mid,right);//�պ�

			}
		}
	}
	void printArr()//�迭 ���
	{
		std::cout << "whole process\n";//�պ� ���� ���
		for (int i = 0; i < process_arr.size(); i++)
		{
			std::cout << i + 1 << ": ";
			for (int j = 0; j < size; j++)
			{
				std::cout << process_arr[i][j] << " ";
			}
			std::cout << "\n";
		}

		std::cout << "sorted array :";//���ĵ� �迭 ���
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}
	void PrintSpace(int n)//���� ���� ǥ�ø� ���� ���� ��� �Լ�
	{
		int i = 0;
		for (i = 0; i < n; i++)
		{
			printf("   ");
		}
	}

	int min(int x, int y) //�ּҰ� �Լ�
	{
		return (x < y) ? x : y;
	}
private:
	int* arr, * sorted_arr, size;//�迭, ������ ���� �迭, ũ��
	std::vector<int*> process_arr;//���� �����������ϱ� ���� vector
	
};