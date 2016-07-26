#include <iostream>
#include <assert.h>
#include <vector>
#include "BitMap.h"
using namespace std;


struct HashFunc1
{
	size_t BKDRHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;
			return hash;
		}
	}
	size_t operator()(const string& key, size_t capacity)
	{
		return BKDRHash(key.c_str());
	}
};

struct HashFunc2
{
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
		}
		return hash;
	}

	size_t operator()(const string& key, size_t capacity)
	{
		return SDBMHash(key.c_str());
	}
};

struct HashFunc3
{
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}

	size_t operator()(const string& key, size_t capacity)
	{
		return RSHash(key.c_str());
	}
};

struct HashFunc4
{
	size_t APHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}

	size_t operator()(const string& key, size_t capacity)
	{
		return APHash(key.c_str());
	}
};

struct HashFunc5
{
	size_t JSHash(const char *str)
	{
		if (!*str)       
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}

	size_t operator()(const string& key, size_t capacity)
	{
		return JSHash(key.c_str());
	}
};
template <class _HashFunc1 = HashFunc1, class _HashFunc2 = HashFunc2,
					class _HashFunc3 = HashFunc3, class _HashFunc4 = HashFunc4, 
					class _HashFunc5 = HashFunc5>
class BloomFilter
{
public:
	BloomFilter(size_t capacity)
		:bt(capacity)
		, _capacity(capacity)
	{}
	
	void Set(const string& key)
	{
		size_t index1 = _HashFunc1()(key, _capacity);
		size_t index2 = _HashFunc2()(key, _capacity);
		size_t index3 = _HashFunc3()(key, _capacity);
		size_t index4 = _HashFunc4()(key, _capacity);
		size_t index5 = _HashFunc5()(key, _capacity);
		bt.Set(index1%_capacity);
		bt.Set(index2%_capacity);
		bt.Set(index3%_capacity);
		bt.Set(index4%_capacity);
		bt.Set(index5%_capacity);
	}

	bool Test(const string&key)
	{

		size_t index1 = _HashFunc1()(key, _capacity);
		size_t index2 = _HashFunc2()(key, _capacity);
		size_t index3 = _HashFunc3()(key, _capacity);
		size_t index4 = _HashFunc4()(key, _capacity);
		size_t index5 = _HashFunc5()(key, _capacity);

		if (!bt.Test(index1%_capacity))
			return false;
		if (!bt.Test(index2%_capacity))
			return false;
		if (!bt.Test(index3%_capacity))
			return false;
		if (!bt.Test(index4%_capacity))
			return false;
		if (!bt.Test(index5%_capacity))
			return false;
		return true;
	}
protected:
	BitMap bt;
	size_t _capacity;
};

void Test()
{
	BloomFilter<> bf(100);
	bf.Set("1111111111111");
	bf.Set("asdiuadhasio");
	bf.Set("bloom");
	bf.Set("http://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html");

	cout << "Test1  " << bf.Test("1111111111111") << endl;
	cout << "Test2  " << bf.Test("asdiuadhasio") << endl;
	cout << "Test3  " << bf.Test("bloom") << endl;
	cout << "Test4  " << bf.Test("http://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html") << endl;
	cout << "Test5  " << bf.Test("http://www.cnblogs.com/-clq/archive/2012/05/31/2528153.htmr") << endl;
	cout << "Test6  " << bf.Test("sca") << endl;
}

int main()
{
	Test();
	return 0;
}