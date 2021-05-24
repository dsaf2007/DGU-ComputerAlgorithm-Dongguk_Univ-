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

	// 인접행렬 동적 할당, 스펙트럼 배열 생성, 경로 배열 초기화
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

// 인접 행렬 생성
void hamiltonian::make_adj_matrix()
{
	for (int i = 0; i < arr_size; i++)
	{
		for (int j = 0; j < arr_size; j++)
		{

			// i != j 이고, 출발 길이 n인 스펙트럼의 1부터 끝까지의 서브 스트링과 도착 스펙트럼의 시작부터 
			// n-1까지의 서브스트링이 같은지 비교후 같을 시 인접행렬에 추가.
			if (i != j &&
				((sequence[i]).substr(1, str_size - 1) == (sequence[j]).substr(0, str_size - 1)))
			{
				adj_matrix[i][j] = 1;
			}

		}
	}

}


// 인접 행렬 출력
void hamiltonian::show_matrix()
{
	std::cout << std::endl << "\t\t";

	//번호
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << i << " \t";
	}

	std::cout << std::endl << "\t\t";

	// 스펙트럼
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << sequence[i] << "\t";
	}

	std::cout << std::endl << std::endl;
	
	// 경로 존재 유무
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


// 도착한 곳에 갈곳이 있는지 없는지 체크
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


// 이미 한번 왔던 곳인지 체크
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
	// 만약 그래프의 존재하는 버텍스를 다 돌았을 경우
	if (index == arr_size)
	{
		// 끝인지 확인, 끝일 경우 true 반환
		if (check_end(path_vertex[index - 1]))
			return true;
		else
			return false;
	}

	// 끝이 아닐 경우
	for (int v = 0; v < arr_size; v++)
	{
		// 이미 한번 갔었던 곳인지 체크, 아닐 경우 동작 수행
		if (check_path(v, index))
		{
			path_vertex[index] = v;

			if (hamilton_sub(index + 1) == true)
				return true;

			// true 반환 안됐을 경우 경로 삭제
			path_vertex[index] = -1;
		}
	}

	return false;
}


void hamiltonian::hamilton_rec()
{

	// 시작 인덱스 = path[0], 시작점은 반복문으로 모두 수행해봄
	for (int j = 0; j < arr_size; j++)
	{
		path_vertex[0] = j;

		// 경로를 찾았을 경우
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