#include <iostream>
#include <time.h>
//2016112154 Á¤µ¿±¸

void swap(int a_, int b_);
void BubbleSort(int arr[]);
void BubbleSortRecur(int arr[]);


int main()
{
	std::cout << "Hello world";

}




void swap(int a_, int b_)
{
	int temp = a_;
	a_ = b_;
	b_ = temp;
}

void BubbleSort(int arr[])
{
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		for(int j = 0 ; j < i ; j++)
		{
			if (arr[j] > arr[j + 1])swap(arr[j], arr[j + 1]);

		}
}

void BubbleSortRecur(int arr[])
{

}