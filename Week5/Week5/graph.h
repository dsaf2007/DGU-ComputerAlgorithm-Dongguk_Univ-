//2016112154 ������
#pragma once
#include <iostream>
#include <vector>

class Graph
{
public:
	Graph(int length_)//������. �Ѻ��� ���̸� �޾ƿ´�.
	{
		length = length_;
		size = length * length;
		graph.resize(size);
	}

	void insertWeight(int start, int end, int weight)
	{
		graph[start].push_back(std::make_pair(end,weight));
	}

	int getWeight(int start, int end)//�������, ���������� �Է��ϰ� �� ���� ����ġ�� �޾ƿ´�.
	{
		for (int i =0; i<graph[start].size();i++)
		{
		
			if (end == graph[start][i].first)
			{
				return graph[start][i].second;
			}

		}
	}

	void initializeGraph()//�׷��� �ʱ�ȭ
	{
		for (int i = 0; i < length*2-1; i++)
		{
			if (i % 2 == 0)
			{
				for (int j = 0; j < length-1; j++)//���� ���л��� ����ġ �Է� w->
				{
					int w;
					std::cin >> w;
					insertWeight(length * (i/2) + j, length * (i / 2)+j + 1, w);//������ �迭�� 2���� ó�� ���
				}
			}
			else
			{
				for (int j = 0; j < length; j++)//���� ���л��� ����ġ �Է� w^
				{
					int w;
					std::cin >> w;
					insertWeight(length * (i/2) + j, length * (i/2+1) + j, w);
				}
			}
			
		}
	}


	std::vector<std::vector<std::pair<int, int>>> graph;
private:
	int size;
	int length;
	
};
