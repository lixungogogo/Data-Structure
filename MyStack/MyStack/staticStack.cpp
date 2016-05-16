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
函数名称：void Stack<T,N>::Push(const T& a)
函数功能：向栈内加入元素
函数参数：将加入元素值
返回值  ：无
注意事项：要检查容量是否足够
特殊测试：无
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
函数名称：void Stack<T,N>::Pop()
函数功能：元素出栈
函数参数：无
返回值  ：无
注意事项：检查栈是否为空，为空不出栈
特殊测试：空栈出栈
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
函数名称：T& Stack<T,N>::Top()
函数功能：取栈顶元素
函数参数：无
返回值  ：返回栈顶元素的引用
注意事项：1.返回值为引用还可以对栈顶元素进行修改
		 2.检查是否空栈取栈顶元素
特殊测试：空栈取栈顶元素
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
函数名称：bool Stack<T,N>::Empty()
函数功能：检查栈是否为空
函数参数：无
返回值  ：是否为空
注意事项：无
特殊测试：无
********************************************/
template<class T, int N = 10>
bool Stack<T,N>::Empty()
{
	return _size ? false : true;
}
/*******************************************
函数名称：size_t Stack<T,N>::Size()
函数功能：返回栈的长度
函数参数：无
返回值  ：栈的长度
注意事项：无
特殊测试：无
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
