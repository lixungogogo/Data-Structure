#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;


template <class T,int N = 10>
class Stack
{
public:
	Stack()
	{
		_size = 0;
	}
	void Push(const T&);
	void Pop();
	T& Top();
	bool Empty();
	size_t Size();
protected:
	T a[N];
	size_t _size;
};
/*******************************************
�������ƣ�void Stack<T,N>::Push(const T& a)
�������ܣ���ջ�ڼ���Ԫ��
����������������Ԫ��ֵ
����ֵ  ����
ע�����Ҫ��������Ƿ��㹻
������ԣ���
********************************************/
template<class T,int N = 10>
void Stack<T,N>::Push(const T& data)
{
	if (_size < N)
	{
		a[_size++] = data;
	}
}
/*******************************************
�������ƣ�void Stack<T,N>::Pop()
�������ܣ�Ԫ�س�ջ
������������
����ֵ  ����
ע��������ջ�Ƿ�Ϊ�գ�Ϊ�ղ���ջ
������ԣ���ջ��ջ
********************************************/
template<class T, int N = 10>
void Stack<T,N>::Pop()
{
	if (!Empty())
		_size--;
	else
	{
		cout << "Empty";
	}
}
/*******************************************
�������ƣ�T& Stack<T,N>::Top()
�������ܣ�ȡջ��Ԫ��
������������
����ֵ  ������ջ��Ԫ�ص�����
ע�����1.����ֵΪ���û����Զ�ջ��Ԫ�ؽ����޸�
		 2.����Ƿ��ջȡջ��Ԫ��
������ԣ���ջȡջ��Ԫ��
********************************************/
template<class T, int N = 10>
T& Stack<T,N>::Top()
{
	if (!Empty())
		return a[_size - 1];
	cout << "Empty Stack!" << endl;
	return a[0];
}
/*******************************************
�������ƣ�bool Stack<T,N>::Empty()
�������ܣ����ջ�Ƿ�Ϊ��
������������
����ֵ  ���Ƿ�Ϊ��
ע�������
������ԣ���
********************************************/
template<class T, int N = 10>
bool Stack<T,N>::Empty()
{
	return _size ? false : true;
}
/*******************************************
�������ƣ�size_t Stack<T,N>::Size()
�������ܣ�����ջ�ĳ���
������������
����ֵ  ��ջ�ĳ���
ע�������
������ԣ���
********************************************/
template<class T, int N = 10>
size_t Stack<T,N>::Size()
{
	return _size;
}

int Test()
{
	Stack<int, 5> a;
	a.Push(1);
	a.Push(2);
	a.Push(3);
	a.Push(4);
	a.Push(5);
	a.Push(6);
	Stack<int, 5> b;
	b = a;
	return 0;

}
