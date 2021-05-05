#pragma once
#include <iostream>
//2016112154 ������

// node Ŭ����
class RBTreeNode
{
public:
	RBTreeNode(int element, RBTreeNode* left, RBTreeNode* right, char c) //������.
		:element(element), left(left), right(right), color(c) {}

private:
	int element;	// ������
	RBTreeNode* parent;
	RBTreeNode* left;
	RBTreeNode* right;
	int color; // 1==black, 0==red
	friend class RBTree;
};

class RBTree
{
	// ����Ž��Ʈ���� �����ϴ� Ŭ����
public:

	RBTree();
	void RBInsert(int data);
	void insertFix(RBTreeNode*& p);
	void leftRotate(RBTreeNode*& x);
	void rightRotate(RBTreeNode*& x);

	// ���� ���
	void showSub(RBTreeNode* p, int level);
	void showStructure();

private:
	RBTreeNode* head;
};