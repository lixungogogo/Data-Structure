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
		_a.resize((capacity >> 5) + 1);
	}

	bool Set(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		if (!(_a[index] & (1 << num)))
		{
			_a[index] |= (1 << num);
			_size++;
			return true;
		}
		else
			return false;
	}

	bool Reset(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		if (_a[index] & (1 << num))
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

void TestBitMap()
{
	BitMap bt(100);
	bt.Set(11);
	bt.Set(12);
	bt.Set(44);
	bt.Set(33);
	bt.Set(99);
	cout << "11?" << bt.Test(11) << endl;
	cout << "12?" << bt.Test(12) << endl;
	cout << "44?" << bt.Test(44) << endl;
	cout << "33?" << bt.Test(33) << endl;
	cout << "98?" << bt.Test(98) << endl;
	cout << "Size = " << bt.Size() << endl;
	bt.Reset(33);
	cout << "11?" << bt.Test(11) << endl;
	cout << "12?" << bt.Test(12) << endl;
	cout << "44?" << bt.Test(44) << endl;
	cout << "33?" << bt.Test(33) << endl;
	cout << "98?" << bt.Test(98) << endl;
	cout << "Size = " << bt.Size() << endl;
}

int main()
{
	TestBitMap();
	return 0;
}