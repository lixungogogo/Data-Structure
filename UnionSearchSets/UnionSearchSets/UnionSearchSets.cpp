#include <iostream>
#include <assert.h>
#include "UnionSerchSets.h"
using namespace std;

int Find(int n, int m, int r[][2])
{
	UnionSearchSets us(n+1);
	for (int i = 0; i < m; i++)
	{
		us.Union(r[i][0], r[i][1]);
	}
	return us.GetRootNum() - 1;
}

int main()
{
	int r[][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 }};
	cout << Find(5, 3, r) << endl;
	return 0;

}