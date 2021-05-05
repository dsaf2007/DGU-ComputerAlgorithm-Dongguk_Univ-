#pragma once
#include "RBTree.h"

RBTree::RBTree()
{
	head = 0;
}

void RBTree::RBInsert(int data)
{
	RBTreeNode* new_node = new RBTreeNode(data, 0, 0, 0); // ������ ��� ����
	RBTreeNode* temp = head; // ���� �� ��ġ
	RBTreeNode* parent_temp = 0; // ������ ����� �θ� ������

	if (head == 0) //tree empty
	{
		head = new_node;
		new_node->parent = 0;
	}
	else //Ʈ���� ������� ���
	{
		while (temp != 0) // ����ִ� ��ġ�� Ž��
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

	insertFix(new_node);// Ʈ�� ���� ����
}

void RBTree::leftRotate(RBTreeNode * &x)
{
	RBTreeNode* y = x->right;
	x->right = y->left; //x�� �������� y�� ������ ����Ű�� ��
	if (y->left != 0) // y�� ������ ���� �ʾ��� ��� �θ� ������
	{
		y->left->parent = x;
	}

	y->parent = x->parent; // x�� ��ġ�� y�� ���Ƿ�, �θ� ������

	if (x->parent != 0) // �θ��� �ڽ� �����͸� ������
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else // �θ� ���� ���, �� x�� ��Ʈ���� ���
	{
		head = y;
	}

	y->left = x; // y�� ������ x�� ����Ű����.
	x->parent = y; // x�� �θ������͸� ���� 
}

// left rotate�� ��Ī
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
	RBTreeNode* parent_p;	// �θ�������
	RBTreeNode* grandparent_p; // ���θ� ������
	RBTreeNode* uncle_p; // ���� ������
	if (p == head) // �ش� ��尡 ��Ʈ�� ���, ���� �ٲ��ְ� ����.
	{
		p->color = 1;
		return;
	}

	// ��尡 ��Ʈ�� �ƴϰ�, �������̰�, ����� �θ�� ���� �������� ���
	while ((p != head) && (p->color == 0) && (p->parent->color == 0))
	{
		parent_p = p->parent;
		grandparent_p = p->parent->parent;

		if (parent_p == grandparent_p->left) // �θ� ���� �ڽ��� ���
		{
			uncle_p = grandparent_p->right; // ������ ������ �ڽ��̴�.

			// ������ �����ϰ�, �������� ��� = case1.
			if ((uncle_p != 0) && (uncle_p->color == 0))
			{
				p->parent->color = 1;
				uncle_p->color = 1;
				grandparent_p->color = 0;
				p = grandparent_p;
			}
			else
			{
				// ��尡 �θ��� ������ �ڽ��� ���. = case 2.
				if (p == parent_p->right)
				{
					// �·� ���� �� Ŀ���� ���� �θ� ����Ű����.
					leftRotate(parent_p);
					p = parent_p;
					parent_p = p->parent; // parent_p�� �θ��� �θ�
				}

				// ��尡 �θ��� ���� �ڽ��� ��� �ٷ� case3����
				rightRotate(grandparent_p);
				p->parent->color = 1;
				grandparent_p->color = 0;
				p = parent_p;
			}
		}
		else // �θ� ������ �ڽ��� ���. �����ڽ��� ����� ��Ī�̴�.
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
	head->color = 1; // ��Ʈ�� ���� ����������.
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

	if (p != 0) { // �Ű������� ���� �����Ͱ� �ΰ��� �ƴ� ���
		showSub(p->right, level + 1); // ���� �ڽ� ����
		for (int i = 0; i < level; i++)
		{ // ������ ���� ��ŭ tab 
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
		showSub(p->left, level + 1); // ���� �ڽ� ����
	}
}