#pragma once
#include "RBTree.h"

RBTree::RBTree()
{
	head = 0;
}

void RBTree::RBInsert(int data)
{
	RBTreeNode* new_node = new RBTreeNode(data, 0, 0, 0); // 삽입할 노드 생성
	RBTreeNode* temp = head; // 삽입 할 위치
	RBTreeNode* parent_temp = 0; // 삽입할 노드의 부모 포인터

	if (head == 0) //tree empty
	{
		head = new_node;
		new_node->parent = 0;
	}
	else //트리가 비어있을 경우
	{
		while (temp != 0) // 비어있는 위치를 탐색
		{
			parent_temp = temp;
			if (temp->element < new_node->element)
				temp = temp->right;
			else
				temp = temp->left;
		}

		new_node->parent = parent_temp;

		if (parent_temp->element > new_node->element)
			parent_temp->left = new_node;
		else
			parent_temp->right = new_node;
	}

	insertFix(new_node);// 트리 구조 수정
}

void RBTree::leftRotate(RBTreeNode * &x)
{
	RBTreeNode* y = x->right;
	x->right = y->left; //x의 오른쪽이 y의 왼쪽을 가리키게 함
	if (y->left != 0) // y의 왼쪽이 비지 않았을 경우 부모를 맞춰줌
	{
		y->left->parent = x;
	}

	y->parent = x->parent; // x의 위치에 y가 오므로, 부모를 맞춰줌

	if (x->parent != 0) // 부모의 자식 포인터를 맞춰줌
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else // 부모가 없는 경우, 즉 x가 루트였을 경우
	{
		head = y;
	}

	y->left = x; // y의 왼쪽이 x를 가리키도록.
	x->parent = y; // x의 부모포인터를 맞춤 
}

// left rotate와 대칭
void RBTree::rightRotate(RBTreeNode * &x)
{

	RBTreeNode* y = x->left;
	x->left = y->right;

	if (x->left != 0)
	{
		x->left->parent = x;
	}

	y->parent = x->parent;

	if (x->parent != 0)
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else
	{
		head = y;
	}

	y->right = x;
	x->parent = y;
}

void RBTree::insertFix(RBTreeNode* &p)
{
	RBTreeNode* parent_p;	// 부모포인터
	RBTreeNode* grandparent_p; // 조부모 포인터
	RBTreeNode* uncle_p; // 삼촌 포인터
	if (p == head) // 해당 노드가 루트일 경우, 색만 바꿔주고 리턴.
	{
		p->color = 1;
		return;
	}

	// 노드가 루트가 아니고, 빨간색이고, 노드의 부모색 또한 빨간색일 경우
	while ((p != head) && (p->color == 0) && (p->parent->color == 0))
	{
		parent_p = p->parent;
		grandparent_p = p->parent->parent;

		if (parent_p == grandparent_p->left) // 부모가 왼쪽 자식일 경우
		{
			uncle_p = grandparent_p->right; // 삼촌은 오른쪽 자식이다.

			// 삼촌이 존재하고, 빨간색일 경우 = case1.
			if ((uncle_p != 0) && (uncle_p->color == 0))
			{
				p->parent->color = 1;
				uncle_p->color = 1;
				grandparent_p->color = 0;
				p = grandparent_p;
			}
			else
			{
				// 노드가 부모의 오른쪽 자식일 경우. = case 2.
				if (p == parent_p->right)
				{
					// 좌로 돌린 뒤 커서가 원래 부모를 가리키도록.
					leftRotate(parent_p);
					p = parent_p;
					parent_p = p->parent; // parent_p는 부모의 부모
				}

				// 노드가 부모의 왼쪽 자식일 경우 바로 case3진입
				rightRotate(grandparent_p);
				p->parent->color = 1;
				grandparent_p->color = 0;
				p = parent_p;
			}
		}
		else // 부모가 오른쪽 자식일 경우. 왼쪽자식일 경우의 대칭이다.
		{
			uncle_p = grandparent_p->left;
			if ((uncle_p != 0) && (uncle_p->color == 0))
			{
				parent_p->color = 1;
				uncle_p->color = 1;
				grandparent_p->color = 0;
				p = grandparent_p;
			}
			else
			{
				if (p == parent_p->left)
				{
					rightRotate(parent_p);
					p = parent_p;
					parent_p = p->parent;
				}
				leftRotate(grandparent_p);
				p->parent->color = 1;
				grandparent_p->color = 0;
				p = parent_p;
			}
		}
	}
	head->color = 1; // 루트의 색을 검은색으로.
}

void RBTree::showStructure()
{
	if (head == 0)
	{
		std::cout << "empty" << std::endl;
	}
	else
	{
		std::cout << std::endl;
		showSub(head, 1);
		std::cout << std::endl;
	}
}

void RBTree::showSub(RBTreeNode* p, int level)
{

	if (p != 0) { // 매개변수로 받은 포인터가 널값이 아닐 경우
		showSub(p->right, level + 1); // 우측 자식 실행
		for (int i = 0; i < level; i++)
		{ // 현재의 레벨 만큼 tab 
			std::cout << '\t';
		}

		std::cout << " " << p->element << " ";
		if (p->color == 1)
			std::cout << "b";
		else
			std::cout << "r";

		if ((p->left != 0) && (p->right != 0))
		{
			std::cout << "<";
		}
		else if (p->right != 0)
		{
			std::cout << "/";
		}
		else if (p->left != 0)
		{
			std::cout << "\\";
		}
		std::cout << std::endl;
		showSub(p->left, level + 1); // 좌측 자식 실행
	}
}