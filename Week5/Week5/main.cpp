//2016112154 ������
#include <iostream>
#include "graph.h"
#include <algorithm>

void greedy()//����ư �׸��� �˰���
{
	Graph g(5);
	std::cout << "insert graph\n";
	g.initializeGraph();
	int pos = 0;
	std::vector<std::pair<int, int>> path;
	std::pair<int, int> max;
	while (pos < 24)//������ ���޽ñ��� �ݺ�
	{
		max = g.graph[pos][0];
		for (int i = 0; i < g.graph[pos].size(); i++)//1�Ǵ� 2ȸ �ݺ�.
		{
			if (max.second < g.graph[pos][i].second)//����ġ�� �� ū���� max�� ����
				max = g.graph[pos][i];
		}
		path.push_back(max);//��ο� push back
		pos = max.first;
	}
	int weight = 0;
	for (int i = 0; i < path.size(); i++)//����ġ �հ�.
	{
		weight += path[i].second;
	}
	std::cout << weight;

	/*for (int i = 0; i < g.graph[12].size(); i++)//�̵� ��� ���
	{
		std::cout<<g.graph[12][i].first<<" ";
	}*/
}


void dp()//���� ��ȹ��
{
	Graph g(5);
	std::cout << "insert graph\n";
	g.initializeGraph();//�׷��� �Է�

	int weight[5][5];//��ġ�� ����ġ
	weight[0][0] = 0;
	for (int i = 1; i < 5; i++)//S(0,0) to S(j,0)
	{
		weight[0][i] = weight[0][i - 1] + g.getWeight(i - 1, i);
	}

	for (int i = 1; i < 5; i++)//S(0,0) to S(0,i)
	{
		weight[i][0]=weight[i-1][0] + g.getWeight((i - 1) * 5,i*5);
	}
	for(int i = 1 ; i <5 ;i++)//�� ��ġ������ ������ ���� ���� ���Ͽ� �� ū�� ����.
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
	for (int n = 1; n <= 11; n++)//n-->1~11����
	{
		std::cout << "M is : " << n << std::endl;
		std::vector<int> dp(n + 1, 100000);//min�� ���� ������ ū ������ �ʱ�ȭ
		dp[0] = 0;
		for (int i = 0; i < 3; i++)
			for (int j = coin[i]; j <= n; j++)
			{
				dp[j] = std::min(dp[j], dp[j - coin[i]] + 1);//���� �������� ���Ͽ� ������.
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