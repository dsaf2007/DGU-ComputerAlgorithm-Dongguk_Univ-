#pragma once
#include <iostream>
#include "bstree.cpp"


class TestData
{
public:

	void setKey(int newKey)
	{
		keyField = newKey;
	}   // Set the key

	int key() const
	{
		return keyField;
	}     // Returns the key

private:

	int keyField;                // Key for the element
};

//--------------------------------------------------------------------

void main()
{
	BSTree<TestData, int> testTree;   // Test binary search tree
	TestData testElement;            // Binary search tree element
	int inputKey;                    // User input key
	char cmd;                        // Input command

	cout << endl << "Commands:" << endl;
	cout << "  +key : Insert (or update) element" << endl;
	cout << "  ?key : Retrieve element" << endl;
	cout << "  -key : Remove element" << endl;
	cout << "  Q    : Quit the test program" << endl;
	cout << endl;

	do
	{
		testTree.showStructure();                     // Output tree

		cout << endl << "Command: ";                  // Read command
		cin >> cmd;
		if (cmd == '+' || cmd == '?' ||
			cmd == '-')
			cin >> inputKey;

		switch (cmd)
		{
		case '+':                                  // insert
			testElement.setKey(inputKey);
			cout << "Insert : key = " << testElement.key()
				<< endl;
			testTree.insert(testElement);
			break;

		case '?':                                  // retrieve
			if (testTree.retrieve(inputKey, testElement))
			{
				cout << "Retrieved : key = "
					<< testElement.key() << endl;
				if (testTree.retrieveLeft(inputKey, testElement))
					cout << "left child is : " << testElement.key() << endl;
				else
					cout << "no left child" << endl;
				if (testTree.retrieveRight(inputKey, testElement))
					cout << "right child is : " << testElement.key() << endl;
				else
					cout << "no right child" << endl;
			}
			else
				cout << "Not found" << endl;
			break;

		case '-':                                  // remove
			if (testTree.remove(inputKey))
				cout << "Removed element" << endl;
			else
				cout << "Not found" << endl;
			break;

		case 'Q': case 'q':                   // Quit test program
			break;



		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
		}
	} while ((cmd != 'Q') && (cmd != 'q'));

}