#pragma once
#include "bstree.h"
#include <iostream>
#include <assert.h>
//--------------------------------------------------------------------

template < class TE, class KF >
BSTreeNode<TE, KF>::BSTreeNode(const TE& elem,
    BSTreeNode<TE, KF>* leftPtr,
    BSTreeNode<TE, KF>* rightPtr)

    // ����Ʈ�� ����.

    : element(elem),
    left(leftPtr),
    right(rightPtr)

{}

//--------------------------------------------------------------------

template < class TE, class KF >
BSTree<TE, KF>::BSTree()

//����ִ� ����Ʈ�� ����

    : root(0)

{}

//--------------------------------------------------------------------

template < class TE, class KF >
BSTree<TE, KF>:: ~BSTree()

//�޸� ����

{
    clear();
}

//--------------------------------------------------------------------

template < class TE, class KF >
void BSTree<TE, KF>::insert(const TE& newElement)


//Ʈ���� newElement����. ������ element�� tree�� ������ ��� �ڷ� ������Ʈ
{
    insertSub(root, newElement);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
void BSTree<TE, KF>::insertSub(BSTreeNode<TE, KF>*& p,
    const TE& newElement)


    //insert�� ������Լ�. p�� newElement�� �ִ´�
{
    if (p == 0)
    {                                                  // ����
        p = new BSTreeNode<TE, KF>(newElement, 0, 0);
        assert(p != 0);
    }
    else if (newElement.key() < p->element.key())
        insertSub(p->left, newElement);                  // ���� �˻�
    else if (newElement.key() > p->element.key())
        insertSub(p->right, newElement);                 //������ �˻�
    else
        p->element = newElement;                        // Update
}

//--------------------------------------------------------------------

template < class TE, class KF >
int BSTree<TE, KF>::retrieve(KF searchKey, TE& searchElement) const


//Ʈ���ȿ� element�� �ִ��� �˻��Ѵ�. �����Ұ�� element�� copy�ϰ� 1�� return�Ѵ�.
{
    return retrieveSub(root, searchKey, searchElement);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
int BSTree<TE, KF>::retrieveSub(BSTreeNode<TE, KF>* p,
    KF searchKey,
    TE& searchElement) const

    //retrieve�Լ��� ����� �Լ�

{
    int result;

    if (p == 0)
        result = 0;
    else if (searchKey < p->element.key())
        result = retrieveSub(p->left, searchKey, searchElement);
    else if (searchKey > p->element.key())
        result = retrieveSub(p->right, searchKey, searchElement);
    else
    {
        searchElement = p->element;
        result = 1;
    }

    return result;
}

template < class TE, class KF >
int BSTree<TE, KF>::retrieveLeft(KF searchKey, TE& searchElement) const


//Ʈ���ȿ� element�� �ִ��� �˻��Ѵ�. �����Ұ�� element�� copy�ϰ� 1�� return�Ѵ�.
{
    return retrieveLeftSub(root, searchKey, searchElement);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
int BSTree<TE, KF>::retrieveLeftSub(BSTreeNode<TE, KF>* p,
    KF searchKey,
    TE& searchElement) const

    //retrieve�Լ��� ����� �Լ�

{
    int result;

    if (p == 0)
        result = 0;
    else if (searchKey < p->element.key())
        result = retrieveLeftSub(p->left, searchKey, searchElement);
    else if (searchKey > p->element.key())
        result = retrieveLeftSub(p->right, searchKey, searchElement);
    else
    {
        if (p->left == nullptr)
            result = 0;
        else
        {
            searchElement = p->left->element;
            result = 1;
        }
    }

    return result;
}

//--------------------------------------------------------------------

template < class TE, class KF >
int BSTree<TE, KF>::retrieveRight(KF searchKey, TE& searchElement) const


//Ʈ���ȿ� element�� �ִ��� �˻��Ѵ�. �����Ұ�� element�� copy�ϰ� 1�� return�Ѵ�.
{
    return retrieveRightSub(root, searchKey, searchElement);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
int BSTree<TE, KF>::retrieveRightSub(BSTreeNode<TE, KF>* p,
    KF searchKey,
    TE& searchElement) const

    //retrieve�Լ��� ����� �Լ�

{
    int result;

    if (p == 0)
        result = 0;
    else if (searchKey < p->element.key())
        result = retrieveRightSub(p->left, searchKey, searchElement);
    else if (searchKey > p->element.key())
        result = retrieveRightSub(p->right, searchKey, searchElement);
    else
    {
        if (p->right == nullptr)
            result = 0;
        else
        {
            searchElement = p->right->element;
            result = 1;
        }
    }

    return result;
}

template < class TE, class KF >
int BSTree<TE, KF>::remove(KF deleteKey)

// Removes the element with key deleteKey from a tree. If the
// element is found, then deletes it from the tree and returns 1.
// Otherwise, returns 0.
//element�� tree�� ������ ��� �����ϰ� 1�� return�Ѵ�.
{
    return removeSub(root, deleteKey);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
int BSTree<TE, KF>::removeSub(BSTreeNode<TE, KF>*& p,
    KF deleteKey)


    //remove�Լ��� ����� �Լ�
    //��尡 children�� �ϳ��� ������ ���� ���� ��� �� ��带 �����Ѵ�.
    //������ �ִ°�쿡�� cutRightmost�� �̿��ؼ� node�� ��ü�ϰ� cutRightmost�� �����Ѵ�.
{
    BSTreeNode<TE, KF>* delPtr;
    int result;

    if (p == 0)
        result = 0;
    else if (deleteKey < p->element.key())
        result = removeSub(p->left, deleteKey);    // Search left
    else if (deleteKey > p->element.key())
        result = removeSub(p->right, deleteKey);   // Search right
    else
    {
        delPtr = p;
        if (p->left == 0)
            p = p->right;                    // left child�������
        else if (p->right == 0)
            p = p->left;                     // right child�������
        else
            cutRightmost(p->left, delPtr);    // ���������
        delete delPtr;
        result = 1;
    }

    return result;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
void BSTree<TE, KF>::cutRightmost(BSTreeNode<TE, KF>*& r,
    BSTreeNode<TE, KF>*& delPtr)


    //removeSub�� ����� ���� �Լ�. ������ ��忡 �ִ� data�� delPtr�� �����ϰ� delPtr�� ������ ��带point�ϰ� �Ѵ�.

{
    if (r->right != 0)
        cutRightmost(r->right, delPtr);   // Continue down to the right
    else
    {
        delPtr->element = r->element;
        delPtr = r;
        r = r->left;
    }
}

//--------------------------------------------------------------------

template < class TE, class KF >
void BSTree<TE, KF>::writeKeys() const

// ������������ ��� key�� ����Ѵ�


{
    writeKeysSub(root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
void BSTree<TE, KF>::writeKeysSub(BSTreeNode<TE, KF>* p) const

//writeKeys�� ����� �Լ�

{
    if (p != 0)
    {
        writeKeysSub(p->left);
        cout << p->element.key() << endl;
        writeKeysSub(p->right);
    }
}

//--------------------------------------------------------------------

template < class TE, class KF >
void BSTree<TE, KF>::clear()

// ��� ��带 �����

{
    clearSub(root);
    root = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF>* p)

// clear�Լ��� ����� �Լ�
{
    if (p != 0)
    {
        clearSub(p->left);
        clearSub(p->right);
        delete p;
    }
}

//--------------------------------------------------------------------

template < class TE, class KF >
int BSTree<TE, KF>::empty() const

// tree�� ����� ��� 1return

{
    return (root == 0);
}

template < class TE, class KF >
void BSTree<TE, KF>::showStructure() const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
    if (root == 0)
        cout << "Empty tree" << endl;
    else
    {
        cout << endl;
        showSub(root, 1);
        cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
void BSTree<TE, KF>::showSub(BSTreeNode<TE, KF>* p,
    int level) const

    // Recursive partner of the showStructure() function. Outputs the
    // subtree whose root node is pointed to by p. Parameter level is the
    // level of this node within the tree.

{
    int j;   // Loop counter

    if (p != 0)
    {
        showSub(p->right, level + 1);         // Output right subtree
        for (j = 0; j < level; j++)    // Tab over to level
            cout << "\t";
        cout << " " << p->element.key();   // Output key
        if ((p->left != 0) &&           // Output "connector"
            (p->right != 0))
            cout << "<";
        else if (p->right != 0)
            cout << "/";
        else if (p->left != 0)
            cout << "\\";
        else
            cout << "|";
        cout << endl;
        showSub(p->left, level + 1);          // Output left subtree
    }
}

template < class TE, class KF >
int BSTree<TE, KF>::height() const
//����Ʈ���� ���̸� ��Ÿ���� �Լ�
{

    return heightSub(root);

}

template < class TE, class KF >
int BSTree<TE, KF>::heightSub(BSTreeNode<TE, KF>* p) const
//height�� ������Լ�
//�� ��忡�� left right�� NULL�� �ɶ����� �̵��ϸ鼭 �������� �̵��Ҷ� ���� ������ l�� +1
//���������� �̵��Ҷ� ������ ������ r�� +1�� �Ͽ� ���� ū ���� ��ȯ
{


    int l = 0;
    int r = 0;

    if (p == NULL)
    {
        return 0;
    }
    {
        l = heightSub(p->left);
        r = heightSub(p->right);
        if (l >= r)
        {
            return (++l);
        }
        else
        {
            return (++r);
        }
    }


}
