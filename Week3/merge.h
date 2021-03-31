#pragma once
#pragma once
#include <vector>

class Merge
{
public:
	Merge(std::vector<int> input)
	{
		size = input.size();
		arr = new int[size];
		sorted_arr = new int[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = input[i];
		}
	}
	~Merge()
	{
		delete[] arr;
		delete[] sorted_arr;
	}
	void merge(int start, int mid, int end)
	{
		
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
		PrintSpace(start);
		std::cout << "[";
		for (int x = start; x < k; x++)
		{
			std::cout << sorted_arr[x] << " ";
		}std::cout << "]\n";
		for (int x = start; x <= end; x++)
		{
			arr[x] = sorted_arr[x];
		}

	}
	void nonRecMerge(int start, int mid, int end)
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
		while (i < size && i <= mid)
		{
			sorted_arr[k++] = arr[i++];
		}
		for (int x = start; x <= end; x++)
		{
			arr[x] = sorted_arr[x];
		}
		for (int x = 0; x < size; x++)
		{
			proc[x] = arr[x];
		}
		process_arr.push_back(proc);
	
	}
	void mergeSort(int start, int end)
	{
		int* proc = new int[size];
		if (start < end)
		{
			int mid = (start + end) / 2;

			mergeSort(start, mid);//left
			mergeSort(mid + 1, end);//right
			merge(start, mid, end);
			for (int i = 0; i < size; i++)
			{
				proc[i] = arr[i];
			}
			process_arr.push_back(proc);


		}
	}

	void nonRecMergeSort()
	{
		int left, right,mid;
		for (int m = 1; m <=size-1; m = 2 * m)
		{
			for (int i = 0; i < size-1; i += 2 * m)
			{
				left = i;
				mid = i + m - 1;
				right = min(i + 2 * m - 1, size-1);

				nonRecMerge(left,mid,right);

			}
		}
	}
	void printArr()
	{
		std::cout << "whole process\n";
		for (int i = 0; i < process_arr.size(); i++)
		{
			std::cout << i + 1 << ": ";
			for (int j = 0; j < size; j++)
			{
				std::cout << process_arr[i][j] << " ";
			}
			std::cout << "\n";
		}

		std::cout << "sorted array :";
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}
	void PrintSpace(int n)
	{
		int i = 0;
		for (i = 0; i < n; i++)
		{
			printf("   ");
		}
	}

	int min(int x, int y) {
		return (x < y) ? x : y;
	}
private:
	int* arr, * sorted_arr, size;
	std::vector<int*> process_arr;
	
};