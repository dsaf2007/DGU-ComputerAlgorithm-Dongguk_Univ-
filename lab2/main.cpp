#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <chrono>
//2016112154 ������

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
	srand(time(NULL));//����ø��� �迭���� �޶����� �ϱ� ����(����1-1)
	int arr_size;//�迭 ũ��
	std::chrono::system_clock::time_point start, end;//nano sec������ �����ϱ� ����
	std::cout << "Enter array size : ";
	std::cin >> arr_size;
	int* array = CreateArr(arr_size);

	//���� 1 ~ 4 �� ���� �׽�Ʈ.
	/*std::cout << "���� �� �迭 :";
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

	//std::cout << "���� �� �迭 :";
	//for (int i = 0; i < arr_size; i++)
	//{
	//	std::cout << array[i] << " ";
	//}
	//std::cout << "\n";
	std::chrono::nanoseconds elapse_time;//����ð�
	int* arr_1 = array; int* arr_2 = array; int* arr_3 = array; int* arr_4 = array; int* arr_5 = array; int* arr_6 = array;//���� �迭�� ���� ���Ĺ������ �����ϱ� ����

	//����
	start = std::chrono::system_clock::now();
	BubbleSort(arr_1,arr_size);
	end = std::chrono::system_clock::now();
	elapse_time = end-start;
	std::cout << "���������� " << arr_size << "�� �����ϴµ� �ð� :" <<elapse_time.count()<<std::endl;
	//��
	start = std::chrono::system_clock::now();
	QuickSort(array, 0, arr_size - 1);
	end = std::chrono::system_clock::now();
	elapse_time = end - start;
	std::cout << "�������� " << arr_size << "�� �����ϴµ� �ð� :" << elapse_time.count() << std::endl;
	//����
	start = std::chrono::system_clock::now();
	SelectionSort(arr_3, arr_size);
	end = std::chrono::system_clock::now();
	elapse_time = end - start;
	std::cout << "���������� " << arr_size << "�� �����ϴµ� �ð� :" << elapse_time.count() << std::endl;
	//��ͷ� ������ ����
	start = std::chrono::system_clock::now();
	RecBubbleSort(arr_4, arr_size);
	end = std::chrono::system_clock::now();
	elapse_time = end - start;
	std::cout << "��͹��������� " << arr_size << "�� �����ϴµ� �ð� :" << elapse_time.count() << std::endl;
	//��ͷ� ������ ��
	start = std::chrono::system_clock::now();
	RecQuickSort(arr_5, 0, arr_size - 1);
	end = std::chrono::system_clock::now();
	elapse_time = end - start;
	std::cout << "����������� " << arr_size << "�� �����ϴµ� �ð� :" << elapse_time.count()<< std::endl;
	//��ͷ� ������ ����
	start = std::chrono::system_clock::now();
	RecSelectionSort(arr_6, arr_size);
	end = std::chrono::system_clock::now();
	elapse_time = end - start;
	std::cout << "��ͼ��������� " << arr_size << "�� �����ϴµ� �ð� :" << elapse_time.count() << std::endl;

}



void swap(int &a, int &b)//�迭�� ��ġ�� �ٲٱ� ���� �Լ�
{
	int temp = b;
	b = a;
	a = temp;
}

int* CreateArr(int size)//������ �迭�� �����ϴ� �Լ�. �Ű������� �迭ũ�⸦ �޴´�.
{
	int* arr = new int[size];

	for (int i = 0; i < size; i++)
		arr[i] = (int)(((double)((rand() << 15) | rand())) / (((RAND_MAX << 15) | RAND_MAX) + 1) * 1000000);

	return arr;
}


void BubbleSort(int arr[],int size)//���� ����
{
	for (int i = 0; i <  size-1;i++)
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])//������ �׸񳢸� ���Ͽ� �������� Ŭ��� swap
			{
				swap(arr[j], arr[j + 1]);
			}
		}
}


void RecBubbleSort(int arr[], int size)//��ͷ� ������ ��������
{
	if (size == 1)return;

	for (int i = 0; i < size-1; i++)
	{
		if (arr[i] > arr[i + 1])
			swap(arr[i], arr[i + 1]);
	}
	RecBubbleSort(arr, size - 1);
}

int Partition(int arr[], int left, int right)//����� �����Ŀ� �ʿ��� ��Ƽ���� ��ȯ�ϴ� �Լ� 
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

void QuickSort(int arr[], int left,int right)//������ Ȱ���Ͽ� partition�� ��ȯ���� ���Ͽ� �κ������� ũ�Ⱑ 1���� ũ�ٸ� stack�� �־� �ݺ��� ����
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

void RecQuickSort(int arr[], int left, int right)//��͸� �̿��� ������
{
	if (left >= right)//���Ұ� �Ѱ��϶�
	{
		return;
	}
	int pivot = left;
	int i = pivot + 1;
	int j = right;

	while (i <= j)
	{//�����Ͱ� ��ĥ �� ����
		while (i <= right && arr[i] <= arr[pivot])i++;
		while (j > left && arr[j] >= arr[pivot])j--;

		if (i > j)//�������� ��
		{
			swap(arr[j], arr[pivot]);//j��°�� pivot�� ����
		}
		else
		{
			swap(arr[i], arr[j]);//i��°�� j��° ����
		}
	}
	RecQuickSort(arr, left, j - 1);//���� ���
	RecQuickSort(arr, j + 1, right);
}

void SelectionSort(int arr[], int size)//��������
{
	int min_index;//�ּ� �ε���
	for (int i = 0; i < size - 1; i++)
	{
		min_index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[min_index] > arr[j])//�ּ� index�� ���� j���� ū���
				min_index = j;//�ּ� index��  j
		}
		swap(arr[min_index], arr[i]); //�ּ� index�� i swap
	}
}

void RecSelectionSort(int arr[], int size)//��ͷ� ������ ���� ����
{
	if (size == 1)return;//�ϳ��ΰ�� �ٷ� return
	int max = 0;
	for (int i = 1; i < size; i++)
	{
		if (arr[max] < arr[i])max = i;//max������ i�� ũ�� max=i
	}
	swap(arr[max], arr[size - 1]);//���� �������� max�� swap
	RecSelectionSort(arr, size - 1);
}