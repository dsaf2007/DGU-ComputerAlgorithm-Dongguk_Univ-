#pragma once
#include "bstree.h"
#include <iostream>
#include <assert.h>
//--------------------------------------------------------------------

template < class TE, class KF >
BSTreeNode<TE, KF>::BSTreeNode(const TE& elem,
    BSTreeNode<TE, KF>* leftPtr,
    BSTreeNode<TE, KF>* rightPtr)

    // 이진트리 생성.

    : element(elem),
    left(leftPtr),
    right(rightPtr)

{}

//--------------------------------------------------------------------

template < class TE, class KF >
BSTree<TE, KF>::BSTree()

//비어있는 이진트리 생성

    : root(0)

{}

//--------------------------------------------------------------------

template < class TE, class KF >
BSTree<TE, KF>:: ~BSTree()

//메모리 해제

{
    clear();
}

//--------------------------------------------------------------------

template < class TE, class KF >
void BSTree<TE, KF>::insert(const TE& newElement)


//트리에 newElement삽입. 동일한 element가 tree에 존재할 경우 자료 업데이트
{
    insertSub(root, newElement);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
void BSTree<TE, KF>::insertSub(BSTreeNode<TE, KF>*& p,
    const TE& newElement)


    //insert의 재귀적함수. p에 newElement를 넣는다
{
    if (p == 0)
    {                                                  // 삽입
        p = new BSTreeNode<TE, KF>(newElement, 0, 0);
        assert(p != 0);
    }
    else if (newElement.key() < p->element.key())
        insertSub(p->left, newElement);                  // 왼쪽 검색
    else if (newElement.key() > p->element.key())
        insertSub(p->right, newElement);                 //오른쪽 검색
    else
        p->element = newElement;                        // Update
}

//--------------------------------------------------------------------

template < class TE, class KF >
int BSTree<TE, KF>::retrieve(KF searchKey, TE& searchElement) const


//트리안에 element가 있는지 검색한다. 존재할경우 element를 copy하고 1을 return한다.
{
    return retrieveSub(root, searchKey, searchElement);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
int BSTree<TE, KF>::retrieveSub(BSTreeNode<TE, KF>* p,
    KF searchKey,
    TE& searchElement) const

    //retrieve함수의 재귀적 함수

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


//트리안에 element가 있는지 검색한다. 존재할경우 element를 copy하고 1을 return한다.
{
    return retrieveLeftSub(root, searchKey, searchElement);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
int BSTree<TE, KF>::retrieveLeftSub(BSTreeNode<TE, KF>* p,
    KF searchKey,
    TE& searchElement) const

    //retrieve함수의 재귀적 함수

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


//트리안에 element가 있는지 검색한다. 존재할경우 element를 copy하고 1을 return한다.
{
    return retrieveRightSub(root, searchKey, searchElement);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
int BSTree<TE, KF>::retrieveRightSub(BSTreeNode<TE, KF>* p,
    KF searchKey,
    TE& searchElement) const

    //retrieve함수의 재귀적 함수

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
//element가 tree에 존재할 경우 제거하고 1을 return한다.
{
    return removeSub(root, deleteKey);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
int BSTree<TE, KF>::removeSub(BSTreeNode<TE, KF>*& p,
    KF deleteKey)


    //remove함수의 재귀적 함수
    //노드가 children을 하나라도 가지고 있지 않을 경우 그 노드를 삭제한다.
    //가지고 있는경우에는 cutRightmost를 이용해서 node를 대체하고 cutRightmost를 삭제한다.
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
            p = p->right;                    // left child없을경우
        else if (p->right == 0)
            p = p->left;                     // right child없을경우
        else
            cutRightmost(p->left, delPtr);    // 다있을경우
        delete delPtr;
        result = 1;
    }

    return result;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
void BSTree<TE, KF>::cutRightmost(BSTreeNode<TE, KF>*& r,
    BSTreeNode<TE, KF>*& delPtr)


    //removeSub의 기능을 돕는 함수. 마지막 노드에 있는 data를 delPtr에 복사하고 delPtr가 마지막 노드를point하게 한다.

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

// 오름차순으로 모든 key를 출력한다


{
    writeKeysSub(root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
void BSTree<TE, KF>::writeKeysSub(BSTreeNode<TE, KF>* p) const

//writeKeys의 재귀적 함수

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

// 모든 노드를 지운다

{
    clearSub(root);
    root = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class TE, class KF >
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF>* p)

// clear함수의 재귀적 함수
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

// tree가 비었을 경우 1return

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
//이진트리의 깊이를 나타내는 함수
{

    return heightSub(root);

}

template < class TE, class KF >
int BSTree<TE, KF>::heightSub(BSTreeNode<TE, KF>* p) const
//height의 재귀적함수
//각 노드에서 left right가 NULL이 될때까지 이동하면서 왼쪽으로 이동할땐 왼쪽 깊이인 l에 +1
//오른쪽으로 이동할땐 오른쪽 깊이인 r에 +1을 하여 둘중 큰 값을 반환
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
