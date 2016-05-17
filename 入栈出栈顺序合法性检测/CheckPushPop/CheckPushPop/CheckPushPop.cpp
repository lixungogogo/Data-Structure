#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <stack>
#include <queue>
using namespace std;
/*****************************************
题目要求：输入函数入栈，出栈顺序，检测出栈合法性
特殊测试：1.{1,2,3,4,5} {1,2,3,4,5}
		 2.{1,2,3,4,5} {4,5,3,2,1}
		 3.{1,2,3,4,5} {4,3,5,2,1}
		 4.{1,2,3,4,5} {4,3,5,1,2}
******************************************/
template <class T>
bool CheckPushPop(T *In, T *Out,int length)
{
	assert(In);
	assert(Out);
	stack<T> s;
	T *in = In;
	T *out = Out;
	while ( in - In < length)
	{
		if (!s.empty()&&s.top() == *out)
		{
			s.pop();
			out++;
		}
		if (*in != *out)
		{
			s.push(*in++);
		}
		else
		{
			in++;
			out++;
		}
	}
	while (!s.empty() && out - Out < length)
	{
		if (*out != s.top())
			return false;
		out++;
		s.pop();
	}
	return true;
}

int TestCheck()
{
	int in[] = { 1, 2, 3, 4, 5 };
	int out[] = { 4,3,5,2,1 };
	bool a = CheckPushPop<int>(in, out, sizeof(in) / sizeof(in[0]));
	return 0;
}

int main()
{
	TestCheck();
	return 0;
}