#include <iostream>

#define defMaxNum 11

class Heap
{
public:
	Heap(int maxNumber = defMaxNum)
	{
		element = new int[maxNumber];
		size = 0;
		maxSize = maxNumber;
	}

	~Heap()
	{
		delete[] element;
	}

	void insert(const int newElement)
	{
		int i;
		i = ++size;
		while ((i != 1) && (newElement > element[i / 2]))
		{
			element[i] = element[i / 2];
			i /= 2;
		}
		element[i] = newElement;
	}

	int removeMax()
	{
		if (!empty())
		{
			int parent, child;
			int temp = element[size];
			int result = element[1];
			parent = 1;
			child = 2;

			while (child <= size)
			{
				if ((child < size) && (element[child] < element[child + 1]))
					child++;
				if (temp >= element[child])
					break;
				element[parent] = element[child];
				parent = child;
				child *= 2;
			}
			element[parent] = temp;
			size--;
			return result;
		}
		else
			return 0;
	}

	// Heap status operations
	int empty() const
	{
		return (size == 0);
	}

	int maxSize, size;
	int* element;
};

void exec_heap()
{
	int n;
	Heap heap;
	//std::cin >> N;
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
		std::cout << arr[i]<<" ";
	}std::cout << "\n";
}

int main()
{
	exec_heap();
}