#include <iostream>
#include <stdlib.h>
#include <time.h>


void swap(int &a, int &b);

void BubbleSort(int arr[],int size);

void RecBubbleSort(int arr[], int size);

int* CreateArr(int size);


int main()
{
	int arr_size;
	std::cout << "Enter array size : ";
	std::cin >> arr_size;
	int* array = CreateArr(arr_size);
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << "\n";
	BubbleSort(array, arr_size);
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << array[i] << " ";
	}

	std::cout << "\n";
}



void swap(int &a, int &b)
{
	int temp = b;
	b = a;
	a = temp;
}

void BubbleSort(int arr[],int size)
{

	for (int i = 0; i <  size-1;i++)
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}

}

int* CreateArr(int size)
{
	int* arr = new int[size];

	for (int i = 0; i < size; i++)
		arr[i] = (int)(((double)((rand() << 15) | rand())) / (((RAND_MAX << 15) | RAND_MAX) + 1) * 1000000);

	return arr;
}

void RecBubbleSort(int arr[], int size)
{
	if (size == 1)return;

	for (int i = 0; i < size-1; i++)
	{
		if (arr[i] > arr[i + 1])
			swap(arr[i], arr[i + 1]);
	}

	RecBubbleSort(arr, size - 1);
}