#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;
/************************************************
题目描述：实现一个栈，要求入栈，出栈以及求最小值函数的
		 时间复杂度都为O（1）
思路分析：设置辅助栈ass,记录每个状态下的最小值，每次插
		 入时，得到辅助栈当前值，和插入的值比较，如果
		 小则插入到最小值栈的就是它，否则就是原来的最
		 小值。
*************************************************/
template <class T>
class Stack
{
public:
	void Push(T data)
	{
		if (s.empty())
		{
			ass.push(data);
		}
		s.push(data);
		if (data < ass.top())
		{
			ass.push(data);
		}
	}
	void Pop()
	{
		if (s.top() == ass.top())
		{
			ass.pop();
		}
		s.pop();
	}
	T Min()
	{
		return ass.top();
	}
private:
	stack<T> s;
	stack<T> ass;
};

int Test()
{
	Stack<int> s;
	int min = 0;
	s.Push(4);
	min = s.Min();
	s.Push(3);
	min = s.Min();
	s.Push(5);
	min = s.Min();
	s.Push(6);
	min = s.Min();
	s.Push(2);
	min = s.Min();
	s.Push(0);
	min = s.Min();
	s.Push(1);
	min = s.Min();
	s.Pop();
	min = s.Min();
	s.Pop();
	min = s.Min();
	s.Pop();
	min = s.Min();
	s.Pop();
	min = s.Min();
	s.Pop();
	min = s.Min();
	s.Pop();
	min = s.Min();
	return 0;
}

int main()
{
	Test();
	return 0;
}