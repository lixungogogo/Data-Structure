#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

template <class K, class V>
struct Pair
{
	K _first;
	V _second;

	Pair(const K& key, const V& value)
		:_first(key)
		, _second(value)
	{}
};

template <class K,int M>
struct BTreeNode
{
	K _keys[M];
	BTreeNode<K, M>* _subs[M + 1];
	BTreeNode<K, M>* _parent;
	int _size;

	BTreeNode()
		:_size(0)
		, _parent(NULL)
	{
		for (int i = 0; i < M ; i++)
		{
			_keys[i] = 0;
			_subs[i] = NULL;
		}
		_subs[M] = NULL;
	}

};

template <class K,int M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}
	Pair<Node*, int> Find(const K& key)
	{
		if (_root == NULL)
			return Pair<Node*, int>(_root, -1);
		Node* cur = _root;
		Node* parent = cur->_parent;
		while (cur)
		{
			size_t i = 0;
			for (; i < cur->_size; i++)
			{
				if (cur->_keys[i] < key)
					//i++;
				{}
				else if(cur->_keys[i] > key)//key < keys[i]
				{
					parent = cur;
					cur = cur->_subs[i];
					i = 0;
					break;
				}
				else if (cur->_keys[i] == key)
					return Pair<Node*, int>(cur, i);
			}

			if (cur && i >= cur->_size)
			{
				Node* child = cur->_subs[i];
				if (child != NULL && child->_keys[child->_size - 1] > key)
					cur = child;
				else 
					return Pair<Node*, int>(cur, -1);//没找到
			}
		}

		return Pair<Node*, int>(parent, -1);
		

	}


	void InsertNewKey(Node* cur, Node* tmp, int newKey)
	{
		if (cur == NULL)
		{
			_root = new Node;
			_root->_keys[0] = newKey;
			_root->_size++;
			return;
		}
		int end = cur->_size - 1;
		while (end >= 0)
		{
			if (cur->_keys[end] > newKey)
			{
				//动key的时候也要动孩子
				cur->_keys[end + 1] = cur->_keys[end];
				cur->_subs[end + 2] = cur->_subs[end + 1];
			}
			else
				break;
			--end;
		}
		cur->_keys[end + 1] = newKey;
		cur->_subs[end + 2] = tmp;
		cur->_size++;
	}


	bool Insert(const K key)
	{
		Pair<Node*,int> result = Find(key);
		if (result._second != -1)
			return false;


		Node* cur = result._first;
 		Node* parent = NULL;
		Node* tmp = NULL;
		int newKey = key;
		while (1)
		{
			InsertNewKey(cur, tmp, newKey);
			if (cur == NULL)
				break;
			//分裂
			if (cur->_size < M)
				break;

			int div = M / 2;
			int index = 0;
			tmp = new Node;
			for (int i = div + 1; i < cur->_size; i++)
			{
				tmp->_keys[index] = cur->_keys[i];
				tmp->_subs[index++] = cur->_subs[i];
				tmp->_size++;
			}

			newKey = cur->_keys[div];

			for (int i = div; i < cur->_size; i++)
				cur->_keys[i] = 0;

			cur->_size = cur->_size - tmp->_size - 1;

			if (cur->_parent == NULL)//_root
			{
				_root = new Node;
				_root->_keys[0] = newKey;
				_root->_subs[0] = cur;
				_root->_subs[1] = tmp;
				_root->_size = 1;

				cur->_parent = tmp->_parent = _root;
				return true;
			}
			Node* newNode = new Node;
			newNode->_subs[0] = cur;
			Node* parent = cur->_parent;
			for (int i = 0; i <= parent->_size; i++)
			{
				if (parent->_subs[i] == cur)
				{	
					parent->_subs[i] = newNode;
					break;
				}
			}
			newNode->_parent = parent;
			cur->_parent = newNode;
			cur = newNode;
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		int i = 0;
		for (; i < root->_size; i++)
		{
			_InOrder(root->_subs[i]);
			cout << root->_keys[i]<<" ";
		}
		_InOrder(root->_subs[i]);
	}
protected:
	Node* _root; 
};

void Test1()
{
	BTree<int, 3> t;
	int a[] = { 53, 75, 139, 49, 145, 36, 101 };
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
		t.Insert(a[i]);
	t.InOrder();
}

void Test2()
{
	BTree<int, 3> t;
	int b[] = { 3, 4, 10, 40,  20, 15, 50, 35, 16,45, 36, 46, 76, 30, 77};
	for (int i = 0; i < sizeof(b) / sizeof(b[0]); i++)
		t.Insert(b[i]);
	t.InOrder();
}

