#include <iostream>
#include "heap.h"

void exec_heap();

int main()
{
	exec_heap();
}

void exec_heap()
{
	int n;
	Heap heap;
	int arr[10];

	for (int i = 0; i < 10; i++)
	{
		std::cin >> n;
		heap.insert(n);
	}
	for (int i = 0; i < 10; i++)
	{
		arr[i] = heap.removeMax();
	}
	for (int i = 0; i < 10; i++)
	{
		std::cout << arr[i] << " ";
	}std::cout << "\n";
}