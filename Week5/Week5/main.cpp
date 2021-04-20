//2016112154 정동구
#include <iostream>
#include "graph.h"
#include <algorithm>

void greedy()//맨해튼 그리디 알고리즘
{
	Graph g(5);
	std::cout << "insert graph\n";
	g.initializeGraph();
	int pos = 0;
	std::vector<std::pair<int, int>> path;
	std::pair<int, int> max;
	while (pos < 24)//종착지 도달시까지 반복
	{
		max = g.graph[pos][0];
		for (int i = 0; i < g.graph[pos].size(); i++)//1또는 2회 반복.
		{
			if (max.second < g.graph[pos][i].second)//가중치가 더 큰값을 max에 대입
				max = g.graph[pos][i];
		}
		path.push_back(max);//경로에 push back
		pos = max.first;
	}
	int weight = 0;
	for (int i = 0; i < path.size(); i++)//가중치 합계.
	{
		weight += path[i].second;
	}
	std::cout << weight;

	/*for (int i = 0; i < g.graph[12].size(); i++)//이동 경로 출력
	{
		std::cout<<g.graph[12][i].first<<" ";
	}*/
}


void dp()//동적 계획법
{
	Graph g(5);
	std::cout << "insert graph\n";
	g.initializeGraph();//그래프 입력

	int weight[5][5];//위치별 가중치
	weight[0][0] = 0;
	for (int i = 1; i < 5; i++)//S(0,0) to S(j,0)
	{
		weight[0][i] = weight[0][i - 1] + g.getWeight(i - 1, i);
	}

	for (int i = 1; i < 5; i++)//S(0,0) to S(0,i)
	{
		weight[i][0]=weight[i-1][0] + g.getWeight((i - 1) * 5,i*5);
	}
	for(int i = 1 ; i <5 ;i++)//각 위치까지의 도착시 무게 합을 비교하여 더 큰값 결정.
		for (int j = 1; j < 5; j++)
		{
			weight[i][j] = std::max((weight[i - 1][j] + g.getWeight((i - 1) * 5 + j, i * 5 + j)), weight[i][j - 1] + g.getWeight(i * 5 + (j - 1), i * 5 + j));
		}
	std::cout << "\n\nweight\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cout << weight[i][j] << "\t";
		}std::cout << "\n";
	}
}

void dpCoin()
{
	int coin[3] = { 1,4,7 };
	for (int n = 1; n <= 11; n++)//n-->1~11까지
	{
		std::cout << "M is : " << n << std::endl;
		std::vector<int> dp(n + 1, 100000);//min을 쓰기 때문에 큰 값으로 초기화
		dp[0] = 0;
		for (int i = 0; i < 3; i++)
			for (int j = coin[i]; j <= n; j++)
			{
				dp[j] = std::min(dp[j], dp[j - coin[i]] + 1);//이전 동전사용과 비교하여 작은값.
			}
		std::cout << "least coin : " << dp[n] << std::endl;
	}

}

int main(void)
{
	//greedy();
	//dp();
	dpCoin();
}