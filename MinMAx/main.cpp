//2016112154 정동구
#include <iostream>
#include <time.h>
int findMin(int arr[], int n)//최소값 return
{
	int i, temp;
	temp = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (temp > arr[i])
			temp = arr[i];
	}
	return temp;
}

int findMax(int arr[], int n)//최대값 return
{
	int i, temp;
	temp = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (temp < arr[i])
			temp = arr[i];
	}
	return temp;
}

void findMinMax(int arr[], int n, int &min, int &max)//
{
	min = arr[0]; max = arr[0];
	int small, large;
	for (int i = 1; i < n - 1; i += 2)
	{
		if (arr[i] < arr[i + 1])//i와 i+1 비교 하여 small, large지정
		{
			small = arr[i];
			large = arr[i + 1];
		}
		else
		{
			small = arr[i+1];
			large = arr[i];
		}
		if (small < min)min = small;//min과 small비교 하여 min 변경
		if (large > max)max = large;//max와 small 비교 하여 max 변경
	}
}

int* CreateArr(int size)
{
	int* arr = new int[size];

	for (int i = 0; i < size; i++)
		arr[i] = (int)(((double)((rand() << 15) | rand())) / (((RAND_MAX << 15) | RAND_MAX) + 1) * 1000000);
	//RAND_MAX보다 큰 수 랜덤 생성.

	return arr;
}
int main(void)
{
	srand(time(NULL));
	int* arr=CreateArr(1000);//1000개 짜리 배열 생성.
	int min, max;
	std::cout << "find min, find mad 이용\n";
	std::cout << "min of arr : " << findMin(arr, 10) << "\n";
	std::cout << "max of arr : " << findMax(arr, 10) << "\n";
	std::cout << "-------------------------------------------\n";
	std::cout << "findMinMax 이용\n";
	findMinMax(arr, 10, min, max);
	std::cout << "min :" << min << ", max :" << max << "\n";
}