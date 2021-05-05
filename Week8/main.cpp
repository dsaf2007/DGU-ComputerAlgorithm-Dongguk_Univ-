#pragma once
//2016112154 Á¤µ¿±¸
#include <iostream>
#include "RBTree.h"



int main()
{
	RBTree test;
	RBTreeNode* t_node;
	int input;
	char cmd;

	std::cout << std::endl << "Commands:" << std::endl;
	std::cout << "  +key : Insert (or update) element" << std::endl;

	do
	{
		std::cout << std::endl;
		test.showStructure();
		std::cout << std::endl << "command : ";
		std::cin >> cmd;
		if (cmd == '+')
			std::cin >> input;
		switch (cmd)
		{

		case '+':
			std::cout << "insert : key = " << input << std::endl;
			test.RBInsert(input);
			break;

		case 'Q': case 'q':
			std::cout << "exit program\n";
			break;

		default:
			std::cout << "invalid command" << std::endl;

		}

	} while ((cmd != 'Q') && (cmd != 'q'));

}