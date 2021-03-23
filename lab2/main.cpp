#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>


void swap(int &a, int &b);

void BubbleSort(int arr[],int size);
void RecBubbleSort(int arr[], int size);

void QuickSort(int arr[], int left,int right);
int Partition(int arr[], int left, int right);
void RecQuickSort(int arr[], int left, int right);

void SelectionSort(int arr[], int size);
void RecSelectionSort(int arr[], int size);

int* CreateArr(int size);


int main()
{
	clock_t start, end;
	int arr_size;
	std::cout << "Enter array size : ";
	std::cin >> arr_size;
	int* array = CreateArr(arr_size);
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << "\n";
	start = clock();
	RecSelectionSort(array, arr_size);
	end = clock();
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

int Partition(int arr[], int left, int right)
{
	int pivot = arr[right];
	int i = left - 1;
	for (int j = left; j < right; j++)
	{
		if (pivot > arr[j])
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[right]);
	return(i + 1);
}

void QuickSort(int arr[], int left,int right)
{
	int stack[10000];
	int top = -1;
	stack[++top] = left;
	stack[++top] = right;
	while (top >= 0)
	{
		int top_right = stack[top--];
		int top_left = stack[top--];
		int p = Partition(arr, top_left, top_right);
		if (p - 1 > top_left)
		{
			stack[++top] = top_left;
			stack[++top] = p - 1;
		}
		if (p + 1 < top_right)
		{
			stack[++top] = p + 1;
			stack[++top] = top_right;
		}
	}
}

void RecQuickSort(int arr[], int left, int right)
{
	if (left >= right)//원소가 한개일때
	{
		return;
	}

	int pivot = left;
	int i = pivot + 1;
	int j = right;

	while (i <= j)
	{//포인터가 겹칠 때 까지
		while (i <= right && arr[i] <= arr[pivot])i++;
		while (j > left && arr[j] >= arr[pivot])j--;

		if (i > j)
		{
			swap(arr[j], arr[pivot]);
		}
		else
		{
			swap(arr[i], arr[j]);
		}
	}
	RecQuickSort(arr, left, j - 1);
	RecQuickSort(arr, j + 1, right);
}

void SelectionSort(int arr[], int size)
{
	int min_index;
	for (int i = 0; i < size - 1; i++)
	{
		min_index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[min_index] > arr[j])
				min_index = j;
		}
		swap(arr[min_index], arr[i]);
	}
}

void RecSelectionSort(int arr[], int size)
{
	if (size == 1)return;
	int max = 0;
	for (int i = 1; i < size; i++)
	{
		if (arr[max] < arr[i])max = i;
	}
	swap(arr[max], arr[size - 1]);
	RecSelectionSort(arr, size - 1);
}