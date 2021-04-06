//2016112154 ������
#include <iostream>
#include <time.h>
int findMin(int arr[], int n)//�ּҰ� return
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

int findMax(int arr[], int n)//�ִ밪 return
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
		if (arr[i] < arr[i + 1])//i�� i+1 �� �Ͽ� small, large����
		{
			small = arr[i];
			large = arr[i + 1];
		}
		else
		{
			small = arr[i+1];
			large = arr[i];
		}
		if (small < min)min = small;//min�� small�� �Ͽ� min ����
		if (large > max)max = large;//max�� small �� �Ͽ� max ����
	}
}

int* CreateArr(int size)
{
	int* arr = new int[size];

	for (int i = 0; i < size; i++)
		arr[i] = (int)(((double)((rand() << 15) | rand())) / (((RAND_MAX << 15) | RAND_MAX) + 1) * 1000000);
	//RAND_MAX���� ū �� ���� ����.

	return arr;
}
int main(void)
{
	srand(time(NULL));
	int* arr=CreateArr(1000);//1000�� ¥�� �迭 ����.
	int min, max;
	std::cout << "find min, find mad �̿�\n";
	std::cout << "min of arr : " << findMin(arr, 10) << "\n";
	std::cout << "max of arr : " << findMax(arr, 10) << "\n";
	std::cout << "-------------------------------------------\n";
	std::cout << "findMinMax �̿�\n";
	findMinMax(arr, 10, min, max);
	std::cout << "min :" << min << ", max :" << max << "\n";
}