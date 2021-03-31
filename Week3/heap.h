//2016112154 ������
#pragma once
#define defMaxNum 11
class Heap
{
public:
	Heap(int maxNumber = defMaxNum)//������
	{
		element = new int[maxNumber];//ũ�� 10���� �ʱ�ȭ
		size = 0;//�ʱ� size=0
		maxSize = maxNumber;
	}

	~Heap()//�Ҹ���
	{
		delete[] element;//�����Ҵ� delete
	}

	void insert(const int newElement)//���� element ����
	{
		int i;
		i = ++size;//������ +1
		while ((i != 1) && (newElement < element[i / 2]))//�Է��ϴ� ���� element[1/2]�ΰ��
		{
			element[i] = element[i / 2];//i�� i/2����
			i /= 2;//i/2
		}
		element[i] = newElement;//i��(i/2)�� �� ����.
	}

	int removeMin()//�ּҰ� ����
	{
		if (!empty())//���� ���� �ʾ��� ��
		{
			int parent, child;
			int temp = element[size];//�ӽð�
			int result = element[1];//root�� �ּҰ��̹Ƿ�
			parent = 1;
			child = 2;

			while (child <= size)
			{
				if ((child < size) && (element[child] > element[child + 1]))//�ּ� ������ �� �籸��
					child++;
				if (temp <= element[child])
					break;
				element[parent] = element[child];
				parent = child;
				child *= 2;
			}
			element[parent] = temp;
			size--;//ũ�� --
			return result;
		}
		else
			return 0;//���� ����ִ� ���
	}

	// Heap status operations
	int empty() const
	{
		return (size == 0);
	}
	int maxSize, size;
	int* element;
};