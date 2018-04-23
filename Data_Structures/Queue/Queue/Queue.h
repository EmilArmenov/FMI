#pragma once
#include <iostream>

template<class T>
class Queue
{
public:
	Queue();
	~Queue();
	Queue(const Queue&);
	Queue&operator=(const Queue&);

private:
	void copyFrom(const Queue&);
	void clean();

public:
	const T& front()const;
	const T& back()const;

	void enqueue(const T&);
	void dequeue();

	bool isEmpty()const;
	void print();

	size_t getSize()const;

private:
	struct node
	{
		T data;
		node* pNext;

		node(const T& newData, node* newPtr = nullptr) :data(newData), pNext(newPtr)
		{}
	};

	size_t curSize;
	node* pFront;
	node* pBack;
};

template<class T>
inline Queue<T>::Queue() : pFront(nullptr), pBack(nullptr), curSize(0)
{
}

template <class T>
inline Queue<T>::~Queue()
{
	clean();
}

template <class T>
inline Queue<T>::Queue(const Queue& rhs)
{
	copyFrom(rhs);
}

template <class T>
inline Queue<T>&Queue<T>::operator=(const Queue &rhs)
{
	if (this != &rhs)
	{
		clean();
		copyFrom(rhs);
	}

	return *this;
}

template <class T>
inline void Queue<T>::clean()
{
	node* destroy;

	while (pFront != nullptr)
	{
		destroy = pFront;
		pFront = pFront->pNext;
		delete destroy;
	}

	pBack = nullptr;
	curSize = 0;
}

template <class T>
inline void Queue<T>::enqueue(const T& element)
{
	if (isEmpty())
	{
		pFront = new node(element);
		pBack = pFront;
		curSize++;
		return;
	}

	pBack->pNext = new node(element);
	pBack = pBack->pNext;
	curSize++;
}

template <class T>
inline void Queue<T>::dequeue()
{
	if (isEmpty())
		throw std::exception("Queue is empty!");

	node* destroy = pFront;
	pFront = pFront->pNext;
	delete destroy;

	curSize--;
}

template <class T>
inline void Queue<T>::copyFrom(const Queue&rhs)
{
	if (rhs.isEmpty())
		return;

	try
	{
		pFront = new node(rhs.pFront->data);

		node* copyFrom = rhs.pFront->pNext;
		node* copyTo = pFront;

		while (copyFrom)
		{
			copyTo->pNext = new node(copyFrom->data);
			copyTo = copyTo->pNext;
			copyFrom = copyFrom->pNext;
		}

		pBack = copyTo;
		curSize = rhs.curSize;
	}
	catch (std::bad_alloc&)
	{
		clean();
		throw;
	}
}

template<class T>
inline const T& Queue<T>::front() const
{
	if (isEmpty())
		throw std::exception("Empty Queue!");

	return pFront->data;
}

template<class T>
inline const T& Queue<T>::back() const
{
	if (isEmpty())
		throw std::exception("Empty Queue!");

	return pBack->data;
}

template <class T>
inline size_t Queue<T>::getSize() const
{
	return curSize;
}

template<class T>
inline void Queue<T>::print()
{
	node* temp = pFront;
	while (temp)
	{
		std::cout << temp->data << " ";
		temp = temp->pNext;
	}
	std::cout << std::endl;
}

template <class T>
inline bool Queue<T>::isEmpty()const
{
	return curSize == 0;
}