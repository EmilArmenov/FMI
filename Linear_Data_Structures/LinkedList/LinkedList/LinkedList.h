#pragma once
#include <iostream>

template<class T>
class LinkedList 
{
public:
	class Iterator;
	LinkedList();
	LinkedList(const LinkedList&);
	LinkedList& operator=(const LinkedList&);
	~LinkedList();

private:
	void copyFrom(const LinkedList&);
	void clean();

public:
	void insertFront(const T& data);
	void insertBack(const T& data);

	const T& back()const;
	const T& front()const;

	const T& back();
	const T& front();

	void removeBack();
	void removeFront();

	void print()const;
	bool search(const T& data)const;
	bool isEmpty()const;

	int getSize()const;

private:
	struct node
	{
		T data;
		node* pNext;
		
		node() :pNext(nullptr) {}
		node(const T& d, node* p = nullptr): data(d), pNext(p) {}
	};

	node* pFront;
	node* pBack;
	int curSize;

public:

	class Iterator 
	{
		friend class LinkedList;
	private:
		node* pNode;

	public:
		Iterator(Iterator& other) :pNode(other.pNode) 
		{}

		Iterator(node* n) : pNode(n) 
		{}

	public:
		const T& operator*() const {
			return pNode->data;
		}

		T& operator*() {
			return pNode->data;
		}

		const T* operator->() const {
			return pNode->*data;
		}

		T* operator->() {
			return pNode->*data;
		}

		Iterator& operator++() 
		{
			pNode = pNode->pNext;
			return *this;
		}

		Iterator operator++(int) 
		{
			Iterator res(*this);
			++(*this);
			return res;
		}

		bool operator==(const Iterator& other) const {
			return pNode == other.pNode;
		}

		bool operator!=(const Iterator& other) const {
			return !(other == *this);
		}

		bool operator<(const Iterator& other) const {
			return pNode->data < other.pNode->data;
		}

		bool operator>(const Iterator& other) const {
			return other.pNode->data < pNode->data;
		}

		node* erase() 
		{
			if (pNode->pNext == nullptr)
				return nullptr;

			node* deleted = pNode->pNext;
			pNode->pNext = deleted->pNext;			
			
			delete deleted;
			return pNode;
		}

		node* insert(const T& elem) 
		{
			if (pNode->pNext == nullptr) 
			{
				pNode->pNext = new node(elem);
				return pNode->pNext;
			}

			node* newNode = new node(elem);
			newNode->pNext = pNode->pNext;
			pNode->pNext = newNode;

			return newNode;
		}
	};

	Iterator begin()const {
		return Iterator(pFront);
	}

	Iterator end()const {
		return Iterator(pBack->pNext);
	}

	Iterator eraseAfter(Iterator& it) 
	{
		if (it.pNode->pNext == pBack)
		{
			pBack = it.pNode;
			pBack->pNext = nullptr;
		}

		it.erase();
		curSize--;
		return it;
	}

	Iterator insertAfter(Iterator& it, const T& elem)
	{
		if (it.pNode == pBack)
			pBack = it.insert(elem);
		
		else
			it.insert(elem);
		
		curSize++;
		return it;
	}
};

template<class T>
inline LinkedList<T>::LinkedList(): curSize(0)
{
	pFront = pBack = new node();
}

template <class T>
inline LinkedList<T>::LinkedList(const LinkedList& rhs)
{
	copyFrom(rhs);
}

template <class T>
inline LinkedList<T>&LinkedList<T>::operator=(const LinkedList &rhs)
{
	if (this != &rhs)
	{
		clean();
		copyFrom(rhs);
	}

	return *this;
}

template <class T>
inline LinkedList<T>::~LinkedList()
{
	clean();
}

template<class T>
inline void LinkedList<T>::copyFrom(const LinkedList & rhs)
{
	if (rhs.isEmpty())
	{
		pFront = pBack = new node();
		return;
	}

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
	catch (std::bad_alloc& ba)
	{
		clean();
		ba.what();
		throw;
	}
}

template<class T>
inline void LinkedList<T>::clean()
{
	node* destroy;

	while (pFront)
	{
		destroy = pFront;
		pFront = pFront->pNext;
		delete destroy;
	}

	pBack = nullptr;
	curSize = 0;
}

template<class T>
inline bool LinkedList<T>::isEmpty() const
{
	return curSize == 0;
}

template<class T>
inline void LinkedList<T>::insertBack(const T & data)
{
	node* newNode = new node(data);
	pBack->pNext = newNode;
	pBack = newNode;
	pBack->pNext = nullptr;

	curSize++;
}

template<class T>
inline void LinkedList<T>::insertFront(const T & data)
{
	node* newNode = new node(data, pFront->pNext);
	pFront->pNext = newNode;

	if (curSize == 0)
		pBack = newNode;

	curSize++;
}

template<class T>
inline const T & LinkedList<T>::back() const
{
	if (isEmpty())
		throw std::exception("Empty List!");

	return pBack->data;
}

template<class T>
inline const T & LinkedList<T>::front() const
{
	if (isEmpty())
		throw std::exception("Empty List!");

	return pFront->pNext->data;
}

template<class T>
inline const T & LinkedList<T>::back()
{
	if (isEmpty())
		throw std::exception("Empty List!");

	return pBack->data;
}

template<class T>
inline const T & LinkedList<T>::front()
{
	if (isEmpty())
		throw std::exception("Empty List!");

	return pFront->pNext->data;
}

template<class T>
inline void LinkedList<T>::removeBack()
{
	if (isEmpty())
		throw std::exception("Empty List!");

	if (getSize() == 1)
	{
		delete pBack;
		pBack = nullptr;
		pFront->pNext = nullptr;
	}
	else
	{
		node* temp = pFront->pNext;
		while (temp->pNext != pBack)
			temp = temp->pNext;

		pBack = temp;
		pBack->pNext = nullptr;
		delete temp->pNext;
	}
	curSize--;
}

template<class T>
inline void LinkedList<T>::removeFront()
{
	if (isEmpty())
		throw std::exception("List is empty!");

	node* destroy = pFront->pNext;
	pFront->pNext = destroy->pNext;
	delete destroy;
	curSize--;
}

template<class T>
inline void LinkedList<T>::print() const
{
	node* temp = pFront->pNext;
	while (temp)
	{
		std::cout << temp->data << ' ';
		temp = temp->pNext;
	}

	if (!isEmpty())
		std::cout << std::endl;
}

template<class T>
inline bool LinkedList<T>::search(const T & data) const
{
	if (isEmpty())
		return false;
	
	node* pSearch = pFront->pNext;
	while (pSearch)
	{
		if (pSearch->data == data)
			return true;
		
		pSearch = pSearch->pNext;
	}

	return false;
}

template<class T>
inline int LinkedList<T>::getSize() const
{
	return curSize;
}
