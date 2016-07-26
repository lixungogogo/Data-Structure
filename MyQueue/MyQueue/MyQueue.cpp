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
�������ƣ�void Queue<T>::Copy(const Queue &a)
�������ܣ����еĸ��ƺ���
����������a
����ֵ  ����
ע�����Ҫע����ģ�庯���п���ģ������Ϊ�Զ���
		 ���͵�������������������
������ԣ�1.����Ϊ��
		 2.ģ�����TΪstring����
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
�������ƣ�void Queue<T>::Clear()
�������ܣ����е�ɾ������
������������
����ֵ  ����
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
�������ƣ�Queue<T>::~Queue()
�������ܣ����е���������
������������
����ֵ  ����
********************************************/
template <class T>
Queue<T>::~Queue()
{
	Clear();
}
/*******************************************
�������ƣ�Queue<T>::Queue(const Queue&a)
�������ܣ����еĿ������캯��
����������const Queue& a
����ֵ  ����
ע�����1.Ҫ���ж���������Ƿ�ΪNULL
		 2.�����Զ��������Լ��������
������ԣ�1.����һ��Ϊ�յĲ���
		 2.ģ������TΪstring����
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
�������ƣ�Queue<T>& Queue<T>::operator=(const Queue& a)
�������ܣ����еĸ�ֵ��������غ���
����������const Queue& a
����ֵ  ��Queue<T>&
ע�����1.��ֹ�Ը�ֵ
		 2.����ֵΪ���ò���������ֵ
		 3.��ǳ��������
������ԣ�1.�Ը�ֵ
		 2.������ֵ
		 3.�������Ϊ��
******************************************************/
template <class T>
Queue<T>& Queue<T>::operator=(const Queue& a)//��ɾ��ԭ���ģ������һ������Clear�����������е���Clear
{
	if (this != &a)
	{
		Clear();
		Copy(a);
	}
	return *this;
}
/*******************************************
�������ƣ�Node<T>* Queue<T>::BuyNode(const T& data)
�������ܣ����нڵ����ɺ���
����������const T& data
����ֵ  �����ɶ��нڵ�
ע�����Ҫ�ж��Ƿ�newʧ�ܣ����newʧ�ܷ��ؿ�
������ԣ���
********************************************/
template <class T>
Node<T>* Queue<T>::BuyNode(const T& data)
{
	Node<T> *pNode = new Node<T>(data);
	if (pNode == NULL)
	{
		cout << "�����ڴ�ʧ��" << endl;
		return NULL;
	}
	return pNode;
}
/*******************************************
�������ƣ�void Queue<T>::Push(const T& data)
�������ܣ����
����������const T& data
����ֵ  ����
ע�����Ҫ�ж��Ƿ�Ϊ�ն�
������ԣ����նӽ�����Ӳ���
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
�������ƣ�void Queue<T>::Pop()
�������ܣ����Ӻ���
������������
����ֵ  ����
ע������ж��Ƿ�Ϊ�նӣ�Ϊ�նӽ��г��Ӳ���
������ԣ��Կնӽ��г��Ӳ���
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
�������ƣ�T& Queue<T>::Front()
�������ܣ����ضӵ�ͷ����ֵ
������������
����ֵ  ��ͷ����ֵ
ע������ж��Ƿ�Ϊ�ն�
������ԣ��Կնӽ��в���
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
�������ƣ�T& Queue<T>::Back()
�������ܣ����ض�β��ֵ
������������
����ֵ  ����β�ڵ�ֵ
ע������ж��Ƿ�Ϊ�ն�
������ԣ��Կնӽ��в���
********************************************/
template <class T>
T& Queue<T>::Back()
{
	if (Empty())
		cout << "Queue is empty" << endl;
	return _tail->_data;
}
/*******************************************
�������ƣ�bool Queue<T>::Empty()const
�������ܣ��пպ���
������������
����ֵ  ����
ע���������Ϊconst������thisָ��Ϊconst
������ԣ���
********************************************/
template <class T>
bool Queue<T>::Empty()const
{
	return _size ? false : true;
}
/*******************************************
�������ƣ�size_t Queue<T>::Size()
�������ܣ����ضӵĳ���
������������
����ֵ  ���ӵĳ���
ע�������
������ԣ���
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