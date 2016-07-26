#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;
enum States
{
	EMPTY,
	EXIST,
	DELETE,
};
template <class K,class V>
struct HashTableNode
{
	K _key;
	V _value;
	HashTableNode()
	{}
	HashTableNode(K key, V value)
		:_key(key)
		, _value(value)
	{}
	bool operator ==(const HashTableNode& a)
	{
		return (_key == a._key) && (_value == a._value);
	}
};

template <class K,class T>
struct HashFunc
{
	size_t operator()(const K& key, size_t _capacity)
	{
		return key%_capacity;
	}
};

template <class V>
struct HashFunc<string,V>
{
	size_t operator()(const string& key, size_t _capacity)
	{
		int temp = 0;
		const char*str = key.c_str();
		while (*str)
		{
			temp = temp * 10 + *str++;
		}
		return temp%_capacity;
	}
};
//template <class K>
//size_t _HashFunc(const K& key,size_t _capacity)
//{
//	return key%_capacity;
//}
 //template <>
 //size_t _HashFunc<string>(const string& key,size_t _capacity)
 //{
	// const char* str = key.c_str();
	// int index = 0;
	// while (*str)
	// {
	//	index = index * 10 + *str++;
	// }
	// return index%_capacity;
 //}
template <class K,class V,class HashFunc = HashFunc<K,V>>
class HashTable
{
	typedef HashTableNode<K,V> Node;
public:
	HashTable(size_t capacity)
		:_capacity(capacity)
	{
		_size = 0;
		_tables = new Node[_capacity];
		_states = new States[_capacity];
		for (int i = 0; i < _capacity; i++)
		{
			_states[i] = EMPTY;
		}
	}
	void Swap( HashTable& a)
	{
		swap(_tables, a._tables);
		swap(_states, a._states);
		swap(_size, a._size);
		swap(_capacity, a._capacity);
	}
	void Insert(const K& key,const V& value)
	{
		HashFunc _HashFunc;
		_CheckCapacity();
		size_t index = _HashFunc(key,_capacity);
		int i = 1;//二次探查法
		while (_states[index] == EXIST)
		{
			if (_tables[index]._key == key && _tables[index]._value == value)
				return;
			index = (index + i*i) % _capacity;
		}
		_tables[index]._key = key;
		_tables[index]._value = value;
		_states[index] = EXIST;
		_size++;
	}

	Node* Find(const K& key)
	{
		HashFunc _HashFunc;
		size_t index = _HashFunc(key,_capacity);
		int i = 1;
		while (_states[index] == EXIST)
		{
			if (_tables[index]._key == key)
				return &_tables[index];
			index = (index + i*i) % _capacity;
		}
		return NULL;
	}
	void Remove(const K& key)
	{
		HashFunc _HashFunc;
		size_t index = _HashFunc( key,_capacity);
		while (_states[index] == EXIST)
		{
			if (_tables[index]._key == key)
			{
				break;
			}
			index = (index + i*i) % _capacity;
		}
		if (_states[index] == EXIST)//数存在
		{
			_states[index] = DELETE;
			_size--;
		}
	}
	void Print()
	{
		for (int i = 0; i <_capacity; i++)
		{
			if (_states[i] == EXIST)
			{
				cout << "key = " << _tables[i]._key << " ";
				cout << "value = " << _tables[i]._value << endl;
			}
		}
	}
protected:
	void _CheckCapacity()
	{
		if (_size * 10 / _capacity > 7)
		{
			HashTable temp(2 * _capacity);
			for (int i = 0; i < _capacity; i++)
			{
				if (_states[i] == EXIST)
					temp.Insert(_tables[i]._key,_tables[i]._value);
			}
			this->Swap(temp);
		}
	}
	
protected:
	Node *_tables;
	States *_states;
	size_t _size;
	size_t _capacity;
};


int main()
{
	HashTable<string, string> ht(10);
	ht.Insert("一","abc");
	ht.Insert("2","bbb");
	ht.Insert("3","ccc");
	ht.Insert("4","ddd"); 
	ht.Insert("5","eee");
	ht.Insert("6","fff");
	ht.Insert("7","ggg");
	ht.Insert("8","hhh");
	ht.Insert("9","iii");
	ht.Insert("10","jjj");
	cout << ht.Find("一")->_value << endl;
	return 0;
}