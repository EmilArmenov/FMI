#pragma once
#include <iostream>
#include "../../DynamicArray/DynamicArray/DynamicArray.h"

template <class T>
class PriorityQueue 
{
public:
	void push(const T& val);
	void pop();
	const T& top()const;

public:
	int getSize()const;
	bool isEmpty()const;

private:
	void heapifyUp(int);
	void heapifyDown(int parent);

private:
	DynamicArray<T> heap;
};

template<class T>
inline void PriorityQueue<T>::push(const T & val)
{
	heap.add(val);
	heapifyUp(heap.getSize() - 1);
}

template<class T>
inline void PriorityQueue<T>::pop()
{
	try
	{
		if (!heap.getSize())
			throw std::out_of_range("empty queue");

		heap[0] = heap[heap.getSize() - 1];
		heap.removeBack();
		heapifyDown(0);
	}
	catch (const std::out_of_range& w)
	{
		std::cout << w.what() << '\n';
	}
}

template<class T>
inline const T & PriorityQueue<T>::top() const
{
	try
	{
		if (!heap.getSize())
			throw std::out_of_range("empty queue");

		return heap[0];
	}
	catch (const std::out_of_range& w)
	{
		std::cout << w.what() << '\n';
	}
}

template<class T>
inline int PriorityQueue<T>::getSize() const
{
	return heap.getSize();
}

template<class T>
inline bool PriorityQueue<T>::isEmpty() const
{
	return heap.isEmpty();
}

template<class T>
inline void PriorityQueue<T>::heapifyUp(int i)
{
	int parent = (i - 1) / 2;

	if (i && heap[i] < heap[parent])
	{
		heap.swap(heap[parent], heap[i]);
		heapifyUp(parent);
	}
}

template<class T>
inline void PriorityQueue<T>::heapifyDown(int parent)
{
	int largest = parent;
	int left = 2 * parent + 1;
	int right = 2 * parent + 2;

	if (left < heap.getSize() && heap[left] < heap[largest])
		largest = left;

	if (right < heap.getSize() && heap[right] < heap[largest])
		largest = right;

	if (largest != parent)
	{
		heap.swap(heap[parent], heap[largest]);
		parent = largest;
		heapifyDown(parent);
	}
}
