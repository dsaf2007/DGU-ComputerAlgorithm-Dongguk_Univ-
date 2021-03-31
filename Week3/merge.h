//2016112154 정동구
#pragma once
#include <vector>

class Merge
{
public:
	Merge(std::vector<int> input)//생성자
	{
		size = input.size();//배열 크기
		arr = new int[size];//배열
		sorted_arr = new int[size];//정렬에 이용할 배열
		for (int i = 0; i < size; i++)
		{
			arr[i] = input[i];//배열 초기화
		}
	}
	~Merge()//소멸자
	{
		delete[] arr;
		delete[] sorted_arr;
	}
	void merge(int start, int mid, int end)//재귀합병함수
	{
		
		int i = start, j = mid + 1, k = start;
		//분할 정렬된 리스트 합병
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
		//남아있는 값들 일괄 복사
		if (i > mid)
		{
			for (int x = j; x <= end; x++)
			{
				sorted_arr[k] = arr[x];
				k++;
			}
		}
		else//남아있는 값들 일괄 복사
		{
			for (int x = i; x <= mid; x++)
			{
				sorted_arr[k] = arr[x];
				k++;
			}
		}
		PrintSpace(start);
		std::cout << "[";//분할된 부분들 표시.
		for (int x = start; x < k; x++)
		{
			std::cout << sorted_arr[x] << " ";
		}std::cout << "]\n";
		for (int x = start; x <= end; x++)//임시배열의 리스트를 배열에 복사
		{
			arr[x] = sorted_arr[x];
		}

	}
	void nonRecMerge(int start, int mid, int end)//비재귀 합병함수. 합병함수와 동일. 분할부분 표시가 제대로 되지 않아 그 부분만 제외함 + 마지막에 과정 출력을 위해 vector에 pushback
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
		process_arr.push_back(proc);//정렬 과정 저장
	
	}
	void mergeSort(int start, int end)//재귀 합병 정렬
	{
		int* proc = new int[size];
		if (start < end)
		{
			int mid = (start + end) / 2;

			mergeSort(start, mid);//left
			mergeSort(mid + 1, end);//right
			merge(start, mid, end);//합병
			for (int i = 0; i < size; i++)//과정을 vector에 저장.
			{
				proc[i] = arr[i];
			}
			process_arr.push_back(proc);


		}
	}

	void nonRecMergeSort(int start,int end)//비재귀 합병 정렬
	{
		int left, right,mid;
		//m 사이즈의 블록으로 리스트 분할
		for (int m = 1; m <=end; m = 2 * m)
		{
			for (int i = 0; i < end; i += 2 * m)
			{
				left = i;
				mid = i + m - 1;
				right = min(i + 2 * m - 1, end);

				nonRecMerge(left,mid,right);//합병

			}
		}
	}
	void printArr()//배열 출력
	{
		std::cout << "whole process\n";//합병 과정 출력
		for (int i = 0; i < process_arr.size(); i++)
		{
			std::cout << i + 1 << ": ";
			for (int j = 0; j < size; j++)
			{
				std::cout << process_arr[i][j] << " ";
			}
			std::cout << "\n";
		}

		std::cout << "sorted array :";//정렬된 배열 출력
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}
	void PrintSpace(int n)//분할 과정 표시를 위한 공백 출력 함수
	{
		int i = 0;
		for (i = 0; i < n; i++)
		{
			printf("   ");
		}
	}

	int min(int x, int y) //최소값 함수
	{
		return (x < y) ? x : y;
	}
private:
	int* arr, * sorted_arr, size;//배열, 정렬을 위한 배열, 크기
	std::vector<int*> process_arr;//정렬 과정을저장하기 위한 vector
	
};