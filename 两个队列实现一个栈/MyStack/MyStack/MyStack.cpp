#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <stack>
#include <queue>
using namespace std;

/******************************
题目描述：两个队列实现一个栈
思路分析：使用一个队列作为缓冲队列
******************************/
template <class T>
class MyStack
{
public:
	void Push(T data)
	{
		if (q1.empty())
			q2.push(data);
		else if (q2.empty())
			q1.push(data);
	}
	void Pop()
	{
		if (!q1.empty())
		{
			while (q1.size() > 1)
			{
				q2.push(q1.front());
				q1.pop();
			}
			q1.pop();
		}
		else
		{
			while (q2.size() > 1)
			{
				q1.push(q2.front());
				q2.pop();
			}
			q2.pop();
		}
	}
	void Print()const
	{
		if (q1.empty())
		{
			cout << q2.front() << endl;
			cout << q2.back() << endl;
		}
		else
		{
			cout << q1.front() << endl;
			cout << q1.back() << endl;
		}

	}
private:
	queue<T> q1;
	queue<T> q2;
};

int TestStack()
{
	MyStack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Print();
	s.Pop();
	s.Print();
	s.Pop();
	s.Print();
	s.Pop();
	s.Print();
	s.Push(5);
	s.Push(6);
	s.Print();
	s.Pop();
	s.Print();
	s.Pop();
	s.Print();
	return 0;

}

int main()
{
	TestStack();
	return 0;
}