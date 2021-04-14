//2016112154 정동구
#pragma once
#include <iostream>
#include <vector>

class Graph
{
public:
	Graph(int length_)//생성자. 한변의 길이를 받아온다.
	{
		length = length_;
		size = length * length;
		graph.resize(size);
	}

	void insertWeight(int start, int end, int weight)
	{
		graph[start].push_back(std::make_pair(end,weight));
	}

	int getWeight(int start, int end)//출발지점, 도착지점을 입력하고 그 사이 가중치를 받아온다.
	{
		for (int i =0; i<graph[start].size();i++)
		{
		
			if (end == graph[start][i].first)
			{
				return graph[start][i].second;
			}

		}
	}

	void initializeGraph()//그래프 초기화
	{
		for (int i = 0; i < length*2-1; i++)
		{
			if (i % 2 == 0)
			{
				for (int j = 0; j < length-1; j++)//가로 성분사이 가중치 입력 w->
				{
					int w;
					std::cin >> w;
					insertWeight(length * (i/2) + j, length * (i / 2)+j + 1, w);//일차원 배열을 2차원 처럼 사용
				}
			}
			else
			{
				for (int j = 0; j < length; j++)//세로 성분사이 가중치 입력 w^
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
