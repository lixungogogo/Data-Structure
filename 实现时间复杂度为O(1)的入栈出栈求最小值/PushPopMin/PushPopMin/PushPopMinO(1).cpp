#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;
/************************************************
��Ŀ������ʵ��һ��ջ��Ҫ����ջ����ջ�Լ�����Сֵ������
		 ʱ�临�Ӷȶ�ΪO��1��
˼·���������ø���ջass,��¼ÿ��״̬�µ���Сֵ��ÿ�β�
		 ��ʱ���õ�����ջ��ǰֵ���Ͳ����ֵ�Ƚϣ����
		 С����뵽��Сֵջ�ľ��������������ԭ������
		 Сֵ��
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