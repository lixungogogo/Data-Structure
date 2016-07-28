#pragma once 
#include <iostream>
#include <assert.h>
using namespace std;


class UnionSearchSets
{
public:
	UnionSearchSets(int N)
		:_sets(new int[N])
		, _N(N)
	{
		memset(_sets, -1, sizeof(int)*N);
	}

	int FindRoot(int num)
	{
		if (num < 0 || num > _N)
			return -1;
		while (_sets[num] >= 0)
		{
			num = _sets[num];
		}
		return num;
	}

	void Union(const int r1, const int r2)
	{
		int root1 = FindRoot(r1);
		int root2 = FindRoot(r2);
		if (root1 != root2)
		{
			_sets[root1] += _sets[root2];
			_sets[root2] = root1;
		}
	}

	int GetRootNum()
	{
		int k = 0;
		for (int i = 0; i < _N; i++)
		{
			if (_sets[i] < 0)
				k++;
		}
		return k;
	}


protected:
	int* _sets;
	int _N;
};