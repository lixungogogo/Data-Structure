#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;
/*********************************************
��ĿҪ��һ������ʵ������ջ
˼·��������һ����������˷ֱ���Ϊ����ջ��ջ�׺�ջ����
		 ÿ����ջֻ���ƶ�ջ��ָ�뼴�ɡ����ߵ�ջ����
		 �м��ƶ���ջ������Ϊ������ջ��ָ�����Ϊ1
�ⷨ˵����������ֻ���Ǿ�̬ջ������������Ƕ�̬��������
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
void DoubleStack<T, MaxSize>::Push(T data, int index)//indexΪ0����ʾ���ջ�Ĳ�����Ϊ1��ʾ�ұ�ջ
{
	assert(t[0] != t[1] - 1);//ջ��
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
		assert(t[0] > -1);//ջ��
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