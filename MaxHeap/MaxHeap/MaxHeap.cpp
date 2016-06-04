#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;

template <class T>
class Heap
{
public:
	Heap(const T *a = NULL,size_t size = 0)
		:_size(size)
	{
		for (int i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}
		for (int i = (_a.size() - 2) / 2; i >= 0;i--)//½¨¶Ñ
			_AdjustDown(_a,i,size);
	}
	void Push(const T&data)
	{
		_a.push_back(data);
		_AdjustUp(_a,  _a.size());
	}
	void Pop()
	{
		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		_AdjustDown(_a, 0, _a.size());
	}
	bool Empty()
	{
		return (_a.size() == 0)? true : false;
	}
	size_t Size()
	{
		return _a.size();
	}
	T& GetTop()
	{
		return _a[0];
	}
protected:
	void _AdjustDown(vector<T>& a, int  parent, size_t size)
	{
		assert(a.size() > 0);
		int child = parent * 2 + 1;
		while (child < size)
		{
			if (child + 1 < size && a[child] < a[child + 1])
			{
				child++;
			}
			if (a[child] > a[parent])
			{
				swap(a[child], a[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else break;
		}
	}
	void _AdjustUp(vector<T>&a,size_t size)
	{
		int child = size-1;
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			if (a[parent] < a[child])
			{
				swap(a[parent], a[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else break;
		}
	}
protected:
	vector<T> _a;
	size_t _size;
};

int main()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	Heap<int> x(a, sizeof(a) / sizeof(a[0]));
	x.Push(33);
	x.Pop();
	return 0;
}
