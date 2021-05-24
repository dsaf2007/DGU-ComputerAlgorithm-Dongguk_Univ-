#pragma once
#include "hamiltonian.h"


hamiltonian::hamiltonian(std::string input[], int arrsize)//constructor
{

	arr_size = arrsize;
	//sequence = new std::string[arr_size];
	std::vector<std::string> sequence(arr_size);
	str_size = input[0].length();
	adj_matrix = new int* [arr_size];
	std::vector<std::vector<int>> adj_matrix
	path_vertex = new int[arr_size];

	std::cout << "string size = " << str_size << std::endl;
	std::cout << "arr size = " << arr_size << std::endl;

	// ������� ���� �Ҵ�, ����Ʈ�� �迭 ����, ��� �迭 �ʱ�ȭ
	for (int i = 0; i < arr_size; i++)
	{
		path_vertex[i] = -1;
		sequence[i] = input[i];
		adj_matrix[i] = new int[arr_size];
		for (int j = 0; j < arr_size; j++)
		{
			adj_matrix[i][j] = 0;
		}
	}

}

hamiltonian::~hamiltonian()//destructor
{
	for (int i = 0; i < arr_size; i++)
	{
		delete[] adj_matrix[i];
	}
	delete[] sequence;
	delete[] path_vertex;
}

// ���� ��� ����
void hamiltonian::make_adj_matrix()
{
	for (int i = 0; i < arr_size; i++)
	{
		for (int j = 0; j < arr_size; j++)
		{

			// i != j �̰�, ��� ���� n�� ����Ʈ���� 1���� �������� ���� ��Ʈ���� ���� ����Ʈ���� ���ۺ��� 
			// n-1������ ���꽺Ʈ���� ������ ���� ���� �� ������Ŀ� �߰�.
			if (i != j &&
				((sequence[i]).substr(1, str_size - 1) == (sequence[j]).substr(0, str_size - 1)))
			{
				adj_matrix[i][j] = 1;
			}

		}
	}

}


// ���� ��� ���
void hamiltonian::show_matrix()
{
	std::cout << std::endl << "\t\t";

	//��ȣ
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << i << " \t";
	}

	std::cout << std::endl << "\t\t";

	// ����Ʈ��
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << sequence[i] << "\t";
	}

	std::cout << std::endl << std::endl;
	
	// ��� ���� ����
	for (int i = 0; i < arr_size; i++)
	{

		std::cout << i << sequence[i] << "\t->\t";

		for (int j = 0; j < arr_size; j++)
		{
			std::cout << adj_matrix[i][j] << "\t";
		}

		std::cout << std::endl << std::endl;

	}
}


// ������ ���� ������ �ִ��� ������ üũ
bool hamiltonian::check_end(int index)
{
	int cnt = 0;
	for (int i = 0; i < arr_size; i++)
	{
		if (adj_matrix[index][i] == 1)
			return false;
	}
	return true;
}


// �̹� �ѹ� �Դ� ������ üũ
bool hamiltonian::check_path(int destination, int index)
{
	if (adj_matrix[(path_vertex[index - 1])][destination] == 0)
		return false;

	for (int i = 0; i < index; i++)
	{
		if (path_vertex[i] == destination)
		{
			return false;
		}
	}

	return true;
}

bool hamiltonian::hamilton_sub(int index)
{
	// ���� �׷����� �����ϴ� ���ؽ��� �� ������ ���
	if (index == arr_size)
	{
		// ������ Ȯ��, ���� ��� true ��ȯ
		if (check_end(path_vertex[index - 1]))
			return true;
		else
			return false;
	}

	// ���� �ƴ� ���
	for (int v = 0; v < arr_size; v++)
	{
		// �̹� �ѹ� ������ ������ üũ, �ƴ� ��� ���� ����
		if (check_path(v, index))
		{
			path_vertex[index] = v;

			if (hamilton_sub(index + 1) == true)
				return true;

			// true ��ȯ �ȵ��� ��� ��� ����
			path_vertex[index] = -1;
		}
	}

	return false;
}


void hamiltonian::hamilton_rec()
{

	// ���� �ε��� = path[0], �������� �ݺ������� ��� �����غ�
	for (int j = 0; j < arr_size; j++)
	{
		path_vertex[0] = j;

		// ��θ� ã���� ���
		if (hamilton_sub(1) == true)
		{
			string answer = sequence[j];
			cout << "Path Found!! " << endl;
			cout << j << " ";
			for (int i = 1; i < arr_size; i++)
			{
				std::cout << path_vertex[i] << " ";
				answer = answer + sequence[path_vertex[i]].substr(str_size - 1, 1);
			}
			std::cout << std::endl << answer << std::endl << std::endl;
		}
	}
}