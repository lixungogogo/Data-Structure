#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;
class offset
{
public:
	offset(int x = 0, int y = 0, int dir = 0)
		:_x(x)
		, _y(y)
		, _dir(dir)
	{}
	int _x;
	int _y;
	int _dir;
};

offset Dir[8] = { { -1, 0, 0 }, { -1, 1, 1 }, { 0, 1, 2 }, { 1, 1, 3 },
				  { 1, 0, 4 }, { 1, -1, 5 }, { 0, -1, 6 }, { -1, -1, 7 } };
