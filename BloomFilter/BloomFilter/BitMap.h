#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;


class BitMap
{
public:
	BitMap(size_t capacity)
		:_size(0)
	{
		_a.resize(capacity);
	}
	bool Set(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		if (!(_a[index] & (1 << num)))
		{
			_a[index] |= (1 << num);
			++_size;
			return true;
		}
		else
			return false;
	}

	bool Reset(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		if ((_a[index] & (1 << num)))
		{
			_a[index] &= ~(1 << num);
			--_size;
			return true;
		}
		else
			return false;
	}

	bool Test(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		return (_a[index] & (1 << num));
	}
	size_t Size()
	{
		return _size;
	}

protected:
	vector<int> _a;
	size_t _size;
};