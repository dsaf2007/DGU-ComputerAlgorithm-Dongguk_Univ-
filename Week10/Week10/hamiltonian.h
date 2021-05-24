#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


// 해밀턴 패스 수행할 클래스
class hamiltonian
{
public:
	//constructor
	hamiltonian(std::string input[], int arrsize);
	//destructor
	~hamiltonian();

	// 인접 행렬
	void make_adj_matrix();

	// 인접행렬 출력
	void show_matrix();

	// 중복 방문 체크
	bool check_path(int destination, int index);

	// 헤밀턴 경로 재귀도우미 
	bool hamilton_sub(int index);

	// 해밀턴 경로
	void hamilton_rec();

	// 도착한 곳에 진행 할 위치 있는지 확인
	bool check_end(int index);

private:

	// 경로
	int* path_vertex;

	// 생성되는 스트링
	std::string string_gen;

	// sequence 문자열
	std::string* sequence;

	// 인접행렬
	int** adj_matrix;

	int arr_size;
	int str_size;

};
