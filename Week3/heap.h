//2016112154 정동구
#pragma once
#define defMaxNum 11
class Heap
{
public:
	Heap(int maxNumber = defMaxNum)//생성자
	{
		element = new int[maxNumber];//크기 10으로 초기화
		size = 0;//초기 size=0
		maxSize = maxNumber;
	}

	~Heap()//소멸자
	{
		delete[] element;//동적할당 delete
	}

	void insert(const int newElement)//힙에 element 삽입
	{
		int i;
		i = ++size;//사이즈 +1
		while ((i != 1) && (newElement < element[i / 2]))//입력하는 값이 element[1/2]인경우
		{
			element[i] = element[i / 2];//i에 i/2삽입
			i /= 2;//i/2
		}
		element[i] = newElement;//i에(i/2)에 값 삽입.
	}

	int removeMin()//최소값 제거
	{
		if (!empty())//힙이 비지 않았을 때
		{
			int parent, child;
			int temp = element[size];//임시값
			int result = element[1];//root가 최소값이므로
			parent = 1;
			child = 2;

			while (child <= size)
			{
				if ((child < size) && (element[child] > element[child + 1]))//최소 힙으로 힙 재구성
					child++;
				if (temp <= element[child])
					break;
				element[parent] = element[child];
				parent = child;
				child *= 2;
			}
			element[parent] = temp;
			size--;//크기 --
			return result;
		}
		else
			return 0;//힙이 비어있는 경우
	}

	// Heap status operations
	int empty() const
	{
		return (size == 0);
	}
	int maxSize, size;
	int* element;
};