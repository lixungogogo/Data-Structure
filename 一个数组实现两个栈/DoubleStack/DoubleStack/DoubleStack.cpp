#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;
/*********************************************
题目要求：一个数组实现两个栈
思路分析：将一个数组的两端分别设为两个栈的栈底和栈顶，
		 每次入栈只需移动栈顶指针即可。两边的栈都向
		 中间移动。栈满条件为：两个栈顶指针相差为1
解法说明：本函数只考虑静态栈的情况，不考虑动态增容问题
*********************************************/
template <class T, int MaxSize = 10>
class DoubleStack
{
public:
	DoubleStack()
	{
		b[0] = -1;
		b[1] = MaxSize;
		t[0] = -1;
		t[1] = MaxSize;
	}
	void Push(T data, int index);
	void Pop(int index);
	bool Empty()const;
	bool OverFlow()const;
private:
	int b[2];
	int t[2];
	T Vector[MaxSize];
};

template<class T, int MaxSize = 10>
void DoubleStack<T, MaxSize>::Push(T data, int index)//index为0，表示左边栈的操作，为1表示右边栈
{
	assert(t[0] != t[1] - 1);//栈满
	if (index == 0)//left
	{
		t[index]++;
	}
	if (index == 1)//right
	{
		t[index]--;
	}
	Vector[t[index]] = data;
}
template<class T, int MaxSize = 10>
void DoubleStack<T, MaxSize>::Pop(int index)
{
	if (index == 0)
	{
		assert(t[0] > -1);//栈空
		t[index]--;
	}
	if (index == 1)
	{
		assert(t[1] < MaxSize);
		t[index]++;
	}
}

template<class T, int MaxSize = 10>
bool DoubleStack<T, MaxSize>::Empty()const
{
	return (t[0] == -1 && t[1] == MaxSize);
}

template<class T, int MaxSize = 10>
bool DoubleStack<T, MaxSize>::OverFlow()const
{
	return (t[0] == t[1] - 1);
}
int TestDS()
{
	DoubleStack<int> a;
	a.Push(1, 0);
	a.Push(2, 0);
	a.Push(3, 0);
	a.Push(4, 1);
	a.Push(5, 1);
	a.Pop(0);
	a.Push(7, 0);
	a.Pop(1);
	a.Push(8, 1);

	return 0;

}

int main()
{
	TestDS();
	return 0;
}