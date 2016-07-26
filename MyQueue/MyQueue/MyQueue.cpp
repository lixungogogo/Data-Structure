#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;

template <class T>
class Node
{
public:
	Node(T data = 0, Node<T>* next = NULL)
		:_data(data)
		, _next(next)
	{}
	Node(const Node&);
	Node& operator=(const Node&);
	~Node(){}
	T _data;
	Node<T>* _next;
};

template <class T>
class Queue
{
public:
	Queue(Node<T>* head = NULL, Node<T>* tail = NULL, size_t sz = 0)
		:_head(head)
		, _tail(tail)
		, _size(sz)
	{}
	~Queue();
	Queue(const Queue&);
	Queue& operator=(const Queue&);
	Node<T>* BuyNode(const T& data);
	void Push(const T& data);
	void Pop();
	T& Front();
	T& Back();
	bool Empty() const;
	size_t Size();
	void SetEmpty();
	void Copy(const Queue& a);
	void Clear();
private:
	Node<T> *_head;
	Node<T> *_tail;
	size_t _size;
};
/*******************************************
函数名称：void Queue<T>::Copy(const Queue &a)
函数功能：队列的复制函数
函数参数：a
返回值  ：无
注意事项：要注意在模板函数中考虑模板类型为自定义
		 类型的情况，即考虑深拷贝问题
特殊测试：1.输入为空
		 2.模板参数T为string类型
********************************************/
template <class T>
void Queue<T>::Copy(const Queue &a)
{
	if (a._head == NULL)
		return;
	Node <T>* pTemp = a._head;
	_head = _tail = BuyNode(pTemp->_data);
	Node<T>* pNode = _head;
	while (pTemp != a._tail)
	{
		pTemp = pTemp->_next;
		Node<T>* pNewNode = BuyNode(pTemp->_data);
		pNode->_next = pNewNode;
		pNode = pNode->_next;
		_tail = pNode;
	}
	_size = a._size;
}
/*******************************************
函数名称：void Queue<T>::Clear()
函数功能：队列的删除函数
函数参数：无
返回值  ：无
********************************************/
template <class T>
void Queue<T>::Clear()
{
	Node<T> *pTemp = _head;
	while (_head)
	{
		pTemp = _head;
		_head = _head->_next;
		delete pTemp;
		pTemp = NULL;
	}
	_tail = _head;
	_size = 0;
}
/*******************************************
函数名称：Queue<T>::~Queue()
函数功能：队列的析构函数
函数参数：无
返回值  ：无
********************************************/
template <class T>
Queue<T>::~Queue()
{
	Clear();
}
/*******************************************
函数名称：Queue<T>::Queue(const Queue&a)
函数功能：队列的拷贝构造函数
函数参数：const Queue& a
返回值  ：无
注意事项：1.要先判断输入参数是否为NULL
		 2.考虑自定义类型以及深拷贝问题
特殊测试：1.输入一个为空的参数
		 2.模板类型T为string类型
********************************************/
template <class T>
Queue<T>::Queue(const Queue&a)
{
	if (a.Empty())
	{}
	else
	{
		Copy(a);
	}
}
/******************************************************
函数名称：Queue<T>& Queue<T>::operator=(const Queue& a)
函数功能：队列的赋值运算符重载函数
函数参数：const Queue& a
返回值  ：Queue<T>&
注意事项：1.防止自赋值
		 2.返回值为引用才能连续赋值
		 3.深浅拷贝问题
特殊测试：1.自赋值
		 2.连续赋值
		 3.输入参数为空
******************************************************/
template <class T>
Queue<T>& Queue<T>::operator=(const Queue& a)//先删除原来的，抽象出一个函数Clear，析构函数中调用Clear
{
	if (this != &a)
	{
		Clear();
		Copy(a);
	}
	return *this;
}
/*******************************************
函数名称：Node<T>* Queue<T>::BuyNode(const T& data)
函数功能：队列节点生成函数
函数参数：const T& data
返回值  ：生成队列节点
注意事项：要判断是否new失败，如果new失败返回空
特殊测试：无
********************************************/
template <class T>
Node<T>* Queue<T>::BuyNode(const T& data)
{
	Node<T> *pNode = new Node<T>(data);
	if (pNode == NULL)
	{
		cout << "分配内存失败" << endl;
		return NULL;
	}
	return pNode;
}
/*******************************************
函数名称：void Queue<T>::Push(const T& data)
函数功能：入队
函数参数：const T& data
返回值  ：无
注意事项：要判断是否为空队
特殊测试：给空队进行入队操作
********************************************/
template <class T>
void Queue<T>::Push(const T& data)
{
	Node<T>* temp = BuyNode(data);
	if (Empty())
	{
		_head = _tail = temp;
		_size++;
	}
	else
	{
		_tail->_next = temp;
		_tail = temp;
		_size++;
	}  
}
/*******************************************
函数名称：void Queue<T>::Pop()
函数功能：出队函数
函数参数：无
返回值  ：无
注意事项：判断是否为空队，为空队进行出队操作
特殊测试：对空队进行出队操作
********************************************/
template <class T>
void Queue<T>::Pop()
{
	if (Empty())
	{
		cout << "Queue is empty,cannot Pop" << endl;
		return;
	}
	Node<T> *temp = _head;
	_head = _head->_next;
	delete temp;
	_size--;
}
/*******************************************
函数名称：T& Queue<T>::Front()
函数功能：返回队的头结点的值
函数参数：无
返回值  ：头结点的值
注意事项：判断是否为空队
特殊测试：对空队进行测试
********************************************/
template <class T>
T& Queue<T>::Front()
{
	if (Empty())
	{
		cout << "Queue is empty" << endl;
	}
	return _head->_data;
}
/*******************************************
函数名称：T& Queue<T>::Back()
函数功能：返回队尾的值
函数参数：无
返回值  ：队尾节点值
注意事项：判断是否为空队
特殊测试：对空队进行测试
********************************************/
template <class T>
T& Queue<T>::Back()
{
	if (Empty())
		cout << "Queue is empty" << endl;
	return _tail->_data;
}
/*******************************************
函数名称：bool Queue<T>::Empty()const
函数功能：判空函数
函数参数：无
返回值  ：无
注意事项：函数为const，表明this指针为const
特殊测试：无
********************************************/
template <class T>
bool Queue<T>::Empty()const
{
	return _size ? false : true;
}
/*******************************************
函数名称：size_t Queue<T>::Size()
函数功能：返回队的长度
函数参数：无
返回值  ：队的长度
注意事项：无
特殊测试：无
********************************************/
template <class T>
size_t Queue<T>::Size()
{
	return _size;
}

int main()
{
	Queue<int> a;
	//Queue<int> b;
	a.Push(1);
	a.Push(2);
	a.Push(3);
	a.Push(4);
	a.Push(5);
	//a = b;
	Queue<int> b(a);
	Queue<int> c;
	c.Push(7);
	c.Push(8);
	Queue<int> d;
	d.Push(1);
	d.Push(2);
	d.Push(3);
	d.Push(4);
	d.Push(5);
	d.Push(6);
	c = d = a;

	return 0;
}