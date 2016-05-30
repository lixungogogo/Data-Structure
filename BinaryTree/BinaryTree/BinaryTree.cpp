#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	T data;
	struct BinaryTreeNode<T> *left;
	struct BinaryTreeNode<T> *right;

	BinaryTreeNode(const T d = T(), struct BinaryTreeNode<T> *l = NULL, struct BinaryTreeNode<T> *r = NULL)
		:data(d)
		, left(l)
		,right(r)
	{}
};

template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree(Node *r = NULL)
		:root(new Node(r))
	{}
	BinaryTree(const T*a, size_t size, T invaild);
	BinaryTree(const BinaryTree&);
	BinaryTree& operator=(const BinaryTree&);
	~BinaryTree();
	void PreOrder();
	void InOrder();
	void PostOrder();
	void PreOrder_NonR();
	void InOrder_NonR();
	void PostOrder_NonR();
	void LevelOrder();
	void Clear();
	size_t Size();
	size_t Depth();
	size_t LeafSize();
	size_t GetKLevel(size_t index);

protected:
	void _PreOrder(Node* root);
	void _InOrder(Node* root);
	void _PostOrder(Node *root);
	void _BinaryTree(Node**root, const Node* t);

	Node* _Create(Node * root, const T*a, size_t size, T invaild, size_t &index);
	void _Clear(Node**root);
	size_t _Size(Node *root);
	size_t _Depth(Node *root);
	size_t _LeafSize(Node *root);
	size_t _GetKLevel(Node*root,size_t index);
	void _LevelOrder(Node*root);
protected:
	Node* root;
};

//构造函数
template <class T>
BinaryTree<T>::BinaryTree(const T*a, size_t size, T invaild)
{
	assert(a);
	size_t index = 0;
	root = _Create(root, a, size, invaild, index);
}
//创建结点函数
template <class T>
BinaryTreeNode<T>* BinaryTree<T>::_Create(Node * root, const T*a, size_t size, T invaild, size_t &index)
{
	assert(a);
	if (a[index] == invaild || index >= size)
	{
		return NULL;
	}
	if (root == NULL)
		root = new Node;
	root->data = a[index];
	root->left = _Create(root->left, a, size, invaild, ++index);
	root->right = _Create(root->right, a, size, invaild, ++index);
	return root;
}


template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& a)
{
	_BinaryTree(&root, a.root);
}

template <class T>
void BinaryTree<T>::_BinaryTree(Node**root, const Node* t)
{
	if (t != NULL)
	{
		*root = new Node(t->data);
		_BinaryTree(&(*root)->left, t->left);
		_BinaryTree(&(*root)->right, t->right);
	}
}

template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& a)
{
	if (this != &a)
	{
		if (root != NULL)
			Clear();
		_BinaryTree(&root, a.root);
	}
	return *this;
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
	if (root != NULL)
	{
		Clear();
	}
}

template <class T>
void BinaryTree<T>::Clear()
{
	_Clear(&root->left);
	_Clear(&root->right);
	_Clear(&root);

}
template <class T>
void BinaryTree<T>::_Clear(Node**root)
{
	if (*root == NULL)
		return;
	if ((*root)->left == NULL && (*root)->right == NULL)
	{
		delete *root;
		*root = NULL;
		return;
	}
	_Clear(&(*root)->left);
	_Clear(&(*root)->right);
}




//先序遍历
template <class T>
void BinaryTree<T>::PreOrder()
{
	if (root == NULL)
		return;
	cout << root->data << " ";
	_PreOrder(root->left);
	_PreOrder(root->right);
	cout << endl;
}

template <class T>
void BinaryTree<T>::_PreOrder(Node *root)
{
	if (root == NULL)
		return;
	cout << root->data << " ";
	_PreOrder(root->left);
	_PreOrder(root->right);
}
//中序遍历
template <class T>
void BinaryTree<T>::InOrder()
{
	if (root == NULL)
		return;
	_InOrder(root->left);
	cout << root->data << " ";
	_InOrder(root->right);
	cout << endl;
}

template <class T>
void BinaryTree<T>::_InOrder(Node *root)
{
	if (root == NULL)
		return;
	_InOrder(root->left);
	cout << root->data << " ";
	_InOrder(root->right);
}
//后序遍历
template <class T>
void BinaryTree<T>::PostOrder()
{
	if (root == NULL)
		return;
	_PostOrder(root->left);
	_PostOrder(root->right);
	cout << root->data << " ";
	cout << endl;
}
template <class T>
void BinaryTree<T>::_PostOrder(Node *root)
{
	if (root == NULL)
		return;
	_PostOrder(root->left);
	_PostOrder(root->right);
	cout << root->data << " ";
}
//层级遍历
template <class T>
void BinaryTree<T>::LevelOrder()
{
	if (root == NULL)
		return;
	size_t index = 1;
	cout << root->data << " ";
	if (root->left != NULL)
		cout << root->left->data << " ";
	if (root->right != NULL)
		cout << root->right->data << " ";
	_LevelOrder(root->left);
	_LevelOrder(root->right);
}

template <class T>
void BinaryTree<T>::_LevelOrder(Node*root)
{
	if (root == NULL)
		return;
	if (root->left != NULL)
		cout << root->left->data << " ";
	if (root->right != NULL)
		cout << root->right->data << " ";
}

//求二叉树所有结点个数
template <class T>
size_t BinaryTree<T>::Size()
{
	if (root == NULL)
		return 0;
	return _Size(root);
}

template <class T>
size_t BinaryTree<T>::_Size(Node *root)
{
	if (root == NULL)
		return 0;
	return _Size(root->left) + _Size(root->right) + 1;
}


//求二叉树深度
template <class T>
size_t BinaryTree<T>::Depth()
{
	if (root == NULL)
		return 0;
	return _Depth(root);
}

template <class T>
size_t BinaryTree<T>::_Depth(Node*root)
{
	if (root == NULL)
		return 0;
	size_t left = _Depth(root->left) + 1;
	size_t right = _Depth(root->right) + 1;
	return left > right ? left : right;
}

//求二叉树叶子节点个数
template <class T>
size_t BinaryTree<T>::LeafSize()
{
	if (root == NULL)
		return 0;
	return _LeafSize(root);
}

template <class T>
size_t BinaryTree<T>::_LeafSize(Node *root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;
	return _LeafSize(root->left) + _LeafSize(root->right);
}

//求第K层结点个数
template <class T>
size_t BinaryTree<T>::GetKLevel(size_t index)
{
	if (root == NULL)
		return 0;
	if (index <= 0 || index > Depth())
		return -1;
	if (index == 1)
		return 1;
	return _GetKLevel(root, index);
}
template <class T>
size_t BinaryTree<T>::_GetKLevel(Node *root,size_t index)
{
	if (root == NULL)
		return 0;
	size_t left = 0, right = 0;
	if (index == 2)
	{
		left += (root->left == NULL) ? 0 : 1;
		right = (root->right == NULL) ? 0 : 1;
		return left + right;
	}
	return _GetKLevel(root->left, index - 1) + _GetKLevel(root->right, index - 1);

}


int main()
{
	int a[] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int b[] = { 1, 2, 3, 4 };
	BinaryTree<int> t1(a, sizeof(a) / sizeof(a[0]), '#');
	BinaryTree<int> t2(b,sizeof(b)/sizeof(b[0]),'#');
	t1.PreOrder();
	t2.PreOrder();
	t2 = t1;
	t2.PreOrder();
	return 0;
}