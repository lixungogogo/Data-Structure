#include <iostream>
#include <assert.h>
using namespace std;

enum Color
{
	RED,
	BLACK,
};

template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	Color _col;
	K _key;
	V _value;

	RBTreeNode(const K& key, const V& value)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _col(RED)
	{}
};

template <class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;
		}

		cur = new Node(key, value);
		cur->_parent = parent;
		if (parent->_key > key)
			parent->_left = cur;
		else
			parent->_right = cur;


		while (cur != _root && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather == NULL)
				break;
			if (parent == grandfather->_left)
			{
					Node* uncle = grandfather->_right;
					if (uncle && uncle->_col == RED)//1
					{
						if (cur == parent->_left)
						{
							parent->_col = BLACK;
							uncle->_col = BLACK;
							grandfather->_col = RED;

							cur = grandfather;
							parent = cur->_parent;
						}
						else//第三种情况但是uncle为RED
						{
							RotateL(parent);
							swap(parent, cur);
						}
					}
					else if (cur == parent->_left)//2
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
						break;
					}
				else //3
				{
					RotateL(parent);
					swap(parent, cur);
					//3->2
					RotateR(grandfather);

					parent->_col = BLACK;
					grandfather->_col = RED;
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					if (cur == parent->_right)//第一种情况
					{
						parent->_col = BLACK;
						uncle->_col = BLACK;
						grandfather->_col = RED;

						cur  = grandfather;
						parent = cur->_parent;
					}
					else//第三种情况但是uncle为RED
					{
						RotateR(parent);
						swap(parent, cur);
					}
				}
				else if (cur == parent->_right)//第二种情况
				{
					RotateL(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
					break;
				}
				else //第三种情况
				{
					RotateR(parent);
					swap(parent, cur);
					//3->2
					RotateL(grandfather);

					parent->_col = BLACK;
					grandfather->_col = RED;
					break;
				}
			}
		}
		if (_root->_col == RED)
			_root->_col = BLACK;

	}
	void RotateR(Node* parent)
	{
		assert(parent);
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR != NULL)
			subLR->_parent = parent;
		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;
		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
				subL->_parent = ppNode;
			}
			else
			{
				ppNode->_right = subL;
				subL->_parent = ppNode;
			}
		}

	}

	void RotateL(Node* parent)
	{
		assert(parent);
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL != NULL)
			subRL->_parent = parent;
		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;
		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				subR->_parent = ppNode;
				ppNode->_left = subR;
			}
			else
			{
				subR->_parent = ppNode;
				ppNode->_right = subR;
			}
		}
	}
	bool IsBalance()
	{
		if (_root == NULL)
			return true;
		if (_root->_col != BLACK)
			return false;

		int k = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
				k++;
			cur = cur->_left;
		}

		int count = 0;
		bool x = _IsBalance(_root, k, count);
		cout << "IsBalance?" << x<<endl;
		return x;
		
	}
	bool _IsBalance(Node* root, const int k, int count)
	{
		if (root == NULL)
			return true;
		if (root->_col == RED)
		{
			if (root->_parent->_col == RED)
			{
				cout << "两个连续的红结点" << root->_key << endl;
				return false;
			}
		}
		else
			count++;
		if (root->_left == NULL && root->_right == NULL)
		{
			if (k == count)
			{
				return true;
			}
			else
			{
				cout << "两个路径的黑色结点个数不同" << k <<"vs"<<count<< endl;
				return false;
			}
		}
		return _IsBalance(root->_left, k, count)
			&& _IsBalance(root->_right, k, count);
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
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
protected:
	Node* _root;

};

int main()
{
	RBTree<int, int> t;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		t.Insert(a[i], i);
	t.InOrder();
	t.IsBalance();
	}
	return 0;
}