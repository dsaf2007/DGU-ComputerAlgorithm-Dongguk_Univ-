#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


// �ع��� �н� ������ Ŭ����
class hamiltonian
{
public:
	//constructor
	hamiltonian(std::string input[], int arrsize);
	//destructor
	~hamiltonian();

	// ���� ���
	void make_adj_matrix();

	// ������� ���
	void show_matrix();

	// �ߺ� �湮 üũ
	bool check_path(int destination, int index);

	// ����� ��� ��͵���� 
	bool hamilton_sub(int index);

	// �ع��� ���
	void hamilton_rec();

	// ������ ���� ���� �� ��ġ �ִ��� Ȯ��
	bool check_end(int index);

private:

	// ���
	int* path_vertex;

	// �����Ǵ� ��Ʈ��
	std::string string_gen;

	// sequence ���ڿ�
	std::string* sequence;

	// �������
	int** adj_matrix;

	int arr_size;
	int str_size;

};
