#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;

template <class T>
struct Triple
{
	int _row;
	int _col;
	T _value;
	Triple(int x = 0, int y = 0, const T& v = T())
		:_row(x)
		, _col(y)
		, _value(v)
	{}
};

template <class T>
class SparseMatrix
{
public:
	SparseMatrix(const T *a = NULL, size_t M = 0,size_t N = 0, T value = T())
		:_M(M)
		, _N(N)
		, invaild(value)
	{
		if (a != NULL)
		{
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (a[i*N + j] != invaild)
					{
						Triple<T> t(i, j, a[i*N + j]);
						_a.push_back(t);
					}
				}
			}
		}
	}
	SparseMatrix<T> Transport()
	{
		SparseMatrix<T> temp(NULL,_N,_M,invaild);
		for (int i = 0; i < _N; i++)
		{
			for (int j = 0; j < _a.size(); j++)
			{
				if (_a[j]._col == i)
				{
					Triple<T> t(_a[j]._col, _a[j]._row, _a[j]._value);
					temp._a.push_back(t);
				}
			}
		}
		return temp;
	}
	SparseMatrix<T> FastTransport()
	{
		SparseMatrix<T> temp(NULL, _N, _M, invaild);
		temp._a.resize(_a.size());
		int *rowstart = new int[_N];
		memset(rowstart, 0, sizeof(int)*_N);
		int *rowcount = new int[_N];
		memset(rowcount, 0, sizeof(int)*_N);
		for (int i = 0; i < _a.size(); i++)
		{
			rowcount[_a[i]._col]++;
		}
		for (int i = 1; i < _N; i++)
			rowstart[i] = rowstart[i - 1] + rowcount[i - 1];
		for (int i = 0; i < _a.size(); i++)
		{
			int j = rowstart[_a[i]._col];
			temp._a[j]._row = _a[i]._col;
			temp._a[j]._col = _a[i]._row;
			temp._a[j]._value = _a[i]._value;
			rowstart[_a[i]._col]++;
		}
		delete[]rowstart;
		delete[]rowcount;
		return temp;
	}
	void Display()
	{
		size_t index = 0;
		for (int i = 0; i < _M; i++)
		{
			for (int j = 0; j < _N; j++)
			{
				if (_a[index]._row == i && _a[index]._col == j)
				{
					cout << _a[index]._value << " ";
					if (index < _a.size()-1)
						index++;
				}
				else
					cout << invaild << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
protected:
	vector<Triple<T>> _a;
	size_t _M;
	size_t _N;
	T invaild;
};

int main()
{
	int a[] = {1,0,3,0,5,0,0,0,0,0,0,0,0,0,0,2,0,4,0,6,0,0,0,0,0,0,0,0,0,0};
	SparseMatrix<int> x(a, 6, 5, 0);
	x.Display();
	x.Transport().Display();
	x.FastTransport().Display();
	return 0;
}