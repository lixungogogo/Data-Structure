#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

template<class T,int N = 10>
class DStack
{
public:
	DStack(size_t capacity = N)
		:_capacity(capacity)
	{
		_data = new T[N];
		_size = 0;
	}
	~DStack()
	{
		delete[] _data;
	}
	DStack(const DStack&);
	DStack& operator=(const DStack& a);
	DStack& operator=(DStack s);
	void Push(const T&);
	void Pop();
	T PopData();
	T& Top();
	bool Empty();
	size_t Size();
	void Clear();
	bool CheckCapacity();
protected:
	T* _data;
	size_t _size;
	size_t _capacity;
};
/******************************
函数名称：DStack(const DStack&)
函数功能：动态栈的拷贝构造函数
测试用例：DStack<int> b(a);
注意事项：两个参数的N值必须相同
特殊测试：DStack<int,10> a;
		 DStack<int,20> b(a);
    结果：报错
*******************************/
template<class T, int N = 10>
DStack<T, N>::DStack(const DStack& a)
{
	_data = new T[a._capacity];
	for(size_t i = 0; i < a._size;i++)//考虑T为string的情况,即考虑深拷贝的情况
	{
		_data[i] = a._data[i];
	}
	_size = a._size;
	_capacity = a._capacity;
}
/***************************************
函数名称：DStack& operator=(const DStack&)
函数功能：动态栈的赋值运算符重载函数
测试用例：DStack<int> a;
		 DStack<int> b;
		 b = a;
注意事项：两个参数的N值必须相同
特殊测试：1.自赋值
		 2.N值不相同赋值
		 3.连续赋值 a = b = c
**************************************/
template<class T, int N = 10>
DStack<T,N>& DStack<T,N>::operator=(const DStack& a)
{
	if (this != &a)
	{
		DStack<T, N> temp(a);
		T* pTemp = temp._data;
		temp._data = _data;
		_data = pTemp;
		_size = a._size;
		_capacity = a._capacity;
	}
	return *this;
}
//现代写法
template<class T, int N = 10>
DStack<T, N>& DStack<T, N>::operator=(DStack<T, N> s)
{
	swap(_data, s._data);
	swap(_size, s._size);
	swap(_capacity, s._capacity);
}
/******************************
函数名称：bool CheckCapacity()
函数功能：检查是否需要增容
函数参数：无
返回值  ：是否增容成功
注意事项：要检查是否增容失败
特殊测试：无
*******************************/
template<class T, int N = 10>
bool DStack<T,N>::CheckCapacity()
{
	if (_size >= _capacity)
	{
		T *temp = new T[_capacity*2];//在这里不能用realloc，要考虑T为自定义类型的情况
		if (temp == NULL)
		{
			cout << "增容失败" << endl;
			return false;
		}
		for(size_t i = 0;i < _size;i++)//考虑T为string的情况，即深拷贝情况
		{
			temp[i] = _data[i];//深拷贝
		}
		delete []_data;
		_data = temp;
		_capacity *= 2;
	}
	return true;
}
/*******************************************
函数名称：void DStack<T,N>::Push(const T& a)
函数功能：向栈内加入元素
函数参数：将加入元素值
返回值  ：无
注意事项：要检查是否增容
特殊测试：无
********************************************/
template<class T, int N = 10>
void DStack<T,N>::Push(const T& a)
{
	if(CheckCapacity())
		_data[_size++] = a;
}
/*******************************************
函数名称：void DStack<T,N>::Pop()
函数功能：元素出栈
函数参数：无
返回值  ：无
注意事项：检查栈是否为空，为空不出栈
特殊测试：空栈出栈
********************************************/
template<class T, int N = 10>
void DStack<T,N>::Pop()
{
	if (!Empty())
		_size--;
}
template<class T, int N = 10>
T DStack<T, N>::PopData()
{
	if (!Empty())
	{
		_size--;
		return  _data[_size];
	}
	return -1;
}
/*******************************************
函数名称：T& DStack<T,N>::Top()
函数功能：取栈顶元素
函数参数：无
返回值  ：返回栈顶元素的引用
注意事项：1.返回值为引用还可以对栈顶元素进行修改
		 2.检查是否空栈取栈顶元素
特殊测试：空栈取栈顶元素
********************************************/
template<class T, int N = 10>
T& DStack<T,N>::Top()
{
	if (!Empty())
		return _data[_size - 1];
	cout << "Empty DStack!" << endl;
	return _data[0];
}
/*******************************************
函数名称：bool DStack<T,N>::Empty()
函数功能：检查栈是否为空
函数参数：无
返回值  ：是否为空
注意事项：无
特殊测试：无
********************************************/
template<class T, int N = 10>
bool DStack<T,N>::Empty()
{
	return _size ? false : true;
}
/*******************************************
函数名称：size_t DStack<T,N>::Size()
函数功能：返回栈的长度
函数参数：无
返回值  ：栈的长度
注意事项：无
特殊测试：无
********************************************/
template<class T, int N = 10>
size_t DStack<T,N>::Size()
{
	return _size; 
}

int main()
{
	DStack<int> a;
	int b = a.Top();
	return 0;
}