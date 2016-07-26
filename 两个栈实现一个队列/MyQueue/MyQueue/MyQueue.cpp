#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;
/**********************************
题目描述：两个栈实现一个队列
思路描述：设置一个栈为缓冲栈，在两栈之间进行数据
		 的交换。
***************************************/
template <class T>
class MyQueue
{
public:
	void Push(T data)
	{
		if ((s1.empty() && s2.empty()) || s2.empty())
		{
			s1.push(data);
		}
		else if (s1.empty())
		{
			while (!s2.empty())
			{
				s1.push(s2.top());
				s2.pop();
			}
			s1.push(data);
		}
	}
	void Pop()
	{
		if (s1.empty())
		{
			s2.pop();
		}
		else
		{
			while (s1.size() > 1)
			{
				s2.push(s1.top());
				s1.pop();
			}
			s1.pop();
		}
	}
	void Print()const
	{
		if (s1.empty())
		{
			cout << s2.top() << endl;
		}
		else
		{
			cout << s1.top() << endl;
		}
	}
private:
	stack<T> s1;
	stack<T> s2;
};

int TestMyQueue()
{
	MyQueue<int> q;
	q.Push(1);
	q.Print();
	q.Push(2);
	q.Print();
	q.Push(3);
	q.Print();
	q.Pop();
	q.Print();
	q.Pop();
	q.Print();
	q.Push(4);
	q.Print();
	q.Push(5);
	q.Print();
	q.Pop();
	q.Print();
	return 0;
}

int main()
{
	TestMyQueue();
	return 0;
}