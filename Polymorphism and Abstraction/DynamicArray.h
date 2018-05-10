#pragma once
#include <iostream>

template <class T>
class DynamicArray
{
public:
	DynamicArray();
	explicit DynamicArray(size_t init_cap);
	DynamicArray(const DynamicArray& dyn);
	DynamicArray & operator=(const DynamicArray& rhs);
	DynamicArray(const T* cArr, size_t size);
	~DynamicArray();

public:
	void swap(T& data1, T& data2);
	int find(const T& key)const;
	void add(const T& newData);
	void print()const;

	void removeBack();
	void remove(size_t index);

	void insertAt(size_t index, const T& what);
	const T&operator[](size_t index)const;
	T&operator[](size_t i);
	DynamicArray&operator+=(const DynamicArray& rhs);
	DynamicArray operator+(const DynamicArray& rhs)const;

	size_t getSize()const { return currSize; }
	size_t getCap()const { return cap; }
	bool isEmpty()const { return currSize == 0; }

private:
	void resize(size_t newSize);
	void clear() { delete[] data; currSize = 0; cap = 0; }
	void copyFrom(const DynamicArray& dyn);

private:
	size_t cap, currSize;
	T* data;
};

template <class T>
DynamicArray<T>::DynamicArray() :cap(1), currSize(0), data{ new T[cap] }
{
}

template<class T>
DynamicArray<T>::DynamicArray(size_t init_cap) : cap(init_cap), currSize(0), data{ new T[init_cap] }
{
	for (int i = 0; i < init_cap; i++)
		add(T());
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray & dyn)
{
	copyFrom(dyn);
}

template<class T>
DynamicArray<T>&DynamicArray<T>::operator=(const DynamicArray & rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}

	return*this;
}

template<class T>
inline DynamicArray<T>::DynamicArray(const T * cArr, size_t size) :cap(size), currSize(size), data(new T[size])
{
	try
	{
		for (size_t i = 0; i < size; ++i)
			data[i] = cArr[i];
	}
	catch (const std::bad_alloc& ba)
	{
		clear();
		throw;
	}
}

template<class T>
DynamicArray<T>::~DynamicArray()
{
	clear();
}

template<class T>
inline void DynamicArray<T>::print() const
{
	for (size_t i = 0; i < currSize; i++)
		std::cout << data[i] << ' ';
	
	std::cout << std::endl;
}

template<class T>
void DynamicArray<T>::swap(T & data1, T & data2)
{
	T temp = data1;
	data1 = data2;
	data2 = temp;
}

template<class T>
int DynamicArray<T>::find(const T & key) const
{
	for (int i = 0; i < currSize; i++)
	{
		if (data[i] == key)
			return i;
	}

	return -1;
}

template<class T>
void DynamicArray<T>::add(const T& newData)
{
	if (currSize >= cap - 1)
		resize(cap * 2);

	data[currSize++] = newData;
}

template<class T>
void DynamicArray<T>::removeBack()
{
	if (currSize > 0)
		currSize--;
	else
		throw std::length_error("The array is empty");

	if (currSize * 2 <= cap)
	{
		size_t newCap = ((currSize == 0) ? 1 : cap / 2);
		resize(newCap);
	}
}

template<class T>
void DynamicArray<T>::remove(size_t index)
{
	if (index < 0 || index >= currSize)
		throw std::out_of_range("Index out of range");

	if (index == currSize - 1)
	{
		removeBack();
		return;
	}

	for (size_t i = index; i < currSize - 1; i++)
		swap(data[i], data[i + 1]);

	removeBack();
}

template<class T>
void DynamicArray<T>::resize(size_t newSize)
{
	T* temp = new T[newSize];

	for (size_t i = 0; i < currSize; i++)
		temp[i] = data[i];

	delete[]data;
	data = temp;

	cap = newSize;
}

template<class T>
void DynamicArray<T>::copyFrom(const DynamicArray& rhs)
{
	cap = rhs.cap;
	currSize = rhs.currSize;
	data = new T[cap];

	for (size_t i = 0; i < currSize; i++)
		data[i] = rhs.data[i];
}

template<class T>
void DynamicArray<T>::insertAt(size_t index, const T & what)
{
	if (index == currSize)
	{
		add(what);
		return;
	}
	else if (index < currSize && index >= 0)
	{
		add(what);

		for (size_t i = currSize - 1; i > index; i--)
			swap(data[i], data[i - 1]);

		return;
	}
	else
	{
		throw std::out_of_range("from DynamicArray::insertAt");
	}
}

template<class T>
const T&DynamicArray<T>::operator[](size_t index)const
{
	if (index<0 || index >= currSize)
		throw std::out_of_range("from DynamicArray::operator[] const");

	return data[index];
}

template<class T>
T & DynamicArray<T>::operator[](size_t index)
{
	if (index<0 || index >= currSize)
		throw std::out_of_range("from DynamicArray::operator[] const");

	return data[index];
}

template<class T>
DynamicArray<T> & DynamicArray<T>::operator+=(const DynamicArray & rhs)
{
	if (currSize + rhs.currSize >= cap - 1)
	{
		try
		{
			resize(cap + rhs.cap);
		}
		catch (const std::bad_alloc& exc)
		{
			std::cout << exc.what();
			std::cout << "func operator+= could not resize\n";
		}
	}

	for (size_t i = currSize, j = 0; j < rhs.currSize;)
		data[i++] = rhs.data[j++];

	currSize += rhs.currSize;
	return *this;
}

template<class T>
DynamicArray<T>DynamicArray<T>::operator+(const DynamicArray & rhs) const
{
	DynamicArray temp(*this);
	temp += rhs;
	return temp;
}
