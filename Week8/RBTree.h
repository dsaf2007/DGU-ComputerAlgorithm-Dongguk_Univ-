#pragma once
#include <iostream>
//2016112154 정동구

// node 클래스
class RBTreeNode
{
public:
	RBTreeNode(int element, RBTreeNode* left, RBTreeNode* right, char c) //생성자.
		:element(element), left(left), right(right), color(c) {}

private:
	int element;	// 데이터
	RBTreeNode* parent;
	RBTreeNode* left;
	RBTreeNode* right;
	int color; // 1==black, 0==red
	friend class RBTree;
};

class RBTree
{
	// 이진탐색트리를 관리하는 클래스
public:

	RBTree();
	void RBInsert(int data);
	void insertFix(RBTreeNode*& p);
	void leftRotate(RBTreeNode*& x);
	void rightRotate(RBTreeNode*& x);

	// 구조 출력
	void showSub(RBTreeNode* p, int level);
	void showStructure();

private:
	RBTreeNode* head;
};