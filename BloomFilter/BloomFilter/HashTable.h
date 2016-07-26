#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;

template <class K,class V>
struct HashTableNode
{
	K _key;
	V _value;
	HashTableNode* _pNext;
	HashTableNode(K key, V value)
		:_key(key)
		, _value(value)
		, _pNext(NULL)
	{}
};

template <class K>
struct HashFunc
{
	size_t operator()(const K& key, size_t capacity)
	{
		return key%capacity;
	}
};

template <>
struct HashFunc<string>
{
	size_t operator()(const string& key, size_t capacity)
	{
		const char* str = key.c_str();
		size_t size = 0;
		while (*str != '\0')
		{
			size = size * 10 + *str;
		}
		return size;
	}
};

template <class K,class V,class _HashFunc = HashFunc<K>>
class HashTable
{
	typedef HashTableNode<K, V> Node;
public:
	HashTable(size_t capacity)
		:_capacity(capacity)
		, _size(0)
	{
		_tables.resize(capacity);
	}

	void Insert(const K& key,const V& value)
	{
		_CheckCapacity();
		size_t index = _HashFunc()(key, _capacity);
		Node* p(key, value);
		p->_pNext = _tables[index];
		_tables[index] = p->_pNext;
		++_size;
	}

	bool Remove(const K&key)
	{
		size_t index = _HashFunc()(key, _capacity);
		if (_tables[index] == NULL)
			return false;
		Node* pre = _tables[index];
		Node* cur = pre->_pNext;
		if (pre->_key == key)
		{
			delete pre;
			pre = NULL;
			--_size;
			return true;
		}
		while (cur)
		{
			if (cur->_key == key)
			{
				pre->_pNext = cur->_pNext;
				delete cur;
				cur = NULL;
				--_size;
				return true;
			}
			pre = pre->_pNext;
			cur = cur->_pNext;
		}
		return false;
	}
protected:
	void _CheckCapacity()
	{
		if (_size == _capacity)
		{
			_capacity = _GetPrime(_capacity);
			_a.resize(_capacity);
		}
	}

	size_t _GetPrime(size_t capacity)
	{
		static const unsigned long _PrimeList[28] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,
			786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		int i = 0;
		while (capacity > _PrimeList[i])
		{
			i++;
		}
		return _PrimeList[i];
	}
protected:
	vector<Node*> _tables;
	size_t _capacity;
	size_t _size;
};