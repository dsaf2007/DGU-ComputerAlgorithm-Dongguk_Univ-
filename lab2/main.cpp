#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <chrono>
//2016112154 정동구

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
	srand(time(NULL));//실행시마다 배열값이 달라지게 하기 위해(문제1-1)
	int arr_size;//배열 크기
	std::chrono::system_clock::time_point start, end;//nano sec단위로 측정하기 위함
	std::cout << "Enter array size : ";
	std::cin >> arr_size;
	int* array = CreateArr(arr_size);

	//문제 1 ~ 4 각 정렬 테스트.
	/*std::cout << "정렬 전 배열 :";
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << "\n";*/
	
	////BubbleSort(array,arr_size);
	////RecBubbleSort(array,arr_size);
	////QuickSort(array,0, arr_size-1);
	////RecQuickSort(array,0, arr_size-1);
	////SelectionSort(array,arr_size);
	////RecSelectionSort(array,arr_size);

	//std::cout << "정렬 된 배열 :";
	//for (int i = 0; i < arr_size; i++)
	//{
	//	std::cout << array[i] << " ";
	//}
	//std::cout << "\n";
	std::chrono::nanoseconds elapse_time;//경과시간
	int* arr_1 = array; int* arr_2 = array; int* arr_3 = array; int* arr_4 = array; int* arr_5 = array; int* arr_6 = array;//같은 배열로 각각 정렬방식으로 정렬하기 위해

	//버블
	start = std::chrono::system_clock::now();
	BubbleSort(arr_1,arr_size);
	end = std::chrono::system_clock::now();
	elapse_time = end-start;
	std::cout << "버블정렬의 " << arr_size << "를 정렬하는데 시간 :" <<elapse_time.count()<<std::endl;
	//퀵
	start = std::chrono::system_clock::now();
	QuickSort(array, 0, arr_size - 1);
	end = std::chrono::system_clock::now();
	elapse_time = end - start;
	std::cout << "퀵정렬의 " << arr_size << "를 정렬하는데 시간 :" << elapse_time.count() << std::endl;
	//선택
	start = std::chrono::system_clock::now();
	SelectionSort(arr_3, arr_size);
	end = std::chrono::system_clock::now();
	elapse_time = end - start;
	std::cout << "선택정렬의 " << arr_size << "를 정렬하는데 시간 :" << elapse_time.count() << std::endl;
	//재귀로 구현한 버블
	start = std::chrono::system_clock::now();
	RecBubbleSort(arr_4, arr_size);
	end = std::chrono::system_clock::now();
	elapse_time = end - start;
	std::cout << "재귀버블정렬의 " << arr_size << "를 정렬하는데 시간 :" << elapse_time.count() << std::endl;
	//재귀로 구현한 퀵
	start = std::chrono::system_clock::now();
	RecQuickSort(arr_5, 0, arr_size - 1);
	end = std::chrono::system_clock::now();
	elapse_time = end - start;
	std::cout << "재귀퀵정렬의 " << arr_size << "를 정렬하는데 시간 :" << elapse_time.count()<< std::endl;
	//재귀로 구현한 선택
	start = std::chrono::system_clock::now();
	RecSelectionSort(arr_6, arr_size);
	end = std::chrono::system_clock::now();
	elapse_time = end - start;
	std::cout << "재귀선택정렬의 " << arr_size << "를 정렬하는데 시간 :" << elapse_time.count() << std::endl;

}



void swap(int &a, int &b)//배열의 위치를 바꾸기 위한 함수
{
	int temp = b;
	b = a;
	a = temp;
}

int* CreateArr(int size)//난수로 배열을 생성하는 함수. 매개변수로 배열크기를 받는다.
{
	int* arr = new int[size];

	for (int i = 0; i < size; i++)
		arr[i] = (int)(((double)((rand() << 15) | rand())) / (((RAND_MAX << 15) | RAND_MAX) + 1) * 1000000);

	return arr;
}


void BubbleSort(int arr[],int size)//버블 정렬
{
	for (int i = 0; i <  size-1;i++)
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])//인접한 항목끼리 비교하여 오른쪽이 클경우 swap
			{
				swap(arr[j], arr[j + 1]);
			}
		}
}


void RecBubbleSort(int arr[], int size)//재귀로 구현한 버블정렬
{
	if (size == 1)return;

	for (int i = 0; i < size-1; i++)
	{
		if (arr[i] > arr[i + 1])
			swap(arr[i], arr[i + 1]);
	}
	RecBubbleSort(arr, size - 1);
}

int Partition(int arr[], int left, int right)//비재귀 퀵정렬에 필요한 파티션을 반환하는 함수 
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

void QuickSort(int arr[], int left,int right)//스택을 활용하여 partition의 반환값을 비교하여 부분집합의 크기가 1보다 크다면 stack에 넣어 반복문 수행
{
	int stack[10000];
	int top = -1;
	stack[++top] = left;//push
	stack[++top] = right;
	while (top >= 0)
	{
		int top_right = stack[top--];//pop
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

void RecQuickSort(int arr[], int left, int right)//재귀를 이용한 퀵정렬
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

		if (i > j)//엇갈렸을 때
		{
			swap(arr[j], arr[pivot]);//j번째와 pivot을 스왑
		}
		else
		{
			swap(arr[i], arr[j]);//i번째와 j번째 스왑
		}
	}
	RecQuickSort(arr, left, j - 1);//분할 계산
	RecQuickSort(arr, j + 1, right);
}

void SelectionSort(int arr[], int size)//선택정렬
{
	int min_index;//최소 인덱스
	for (int i = 0; i < size - 1; i++)
	{
		min_index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[min_index] > arr[j])//최소 index의 값이 j보다 큰경우
				min_index = j;//최소 index는  j
		}
		swap(arr[min_index], arr[i]); //최소 index와 i swap
	}
}

void RecSelectionSort(int arr[], int size)//재귀로 구현한 선택 정렬
{
	if (size == 1)return;//하나인경우 바로 return
	int max = 0;
	for (int i = 1; i < size; i++)
	{
		if (arr[max] < arr[i])max = i;//max값보다 i가 크면 max=i
	}
	swap(arr[max], arr[size - 1]);//가장 마지막과 max를 swap
	RecSelectionSort(arr, size - 1);
}