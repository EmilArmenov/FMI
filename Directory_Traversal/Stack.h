#pragma once

template <class T>
class Stack 
{
public:
	Stack();
	Stack(const Stack& rhs);
	Stack& operator=(const Stack& rhs);
	~Stack();

public:
	void push(const T& data);
	void pop();
	T& peek();
	const T& peek()const;
	bool isEmpty()const { return currSize == 0; }
	void print()const;

private:
	void copyFrom(const Stack& rhs);
	void clean();

private:
	struct Node
	{
		T m_data;
		Node* m_pNext;

		Node(const T& data, Node* pNext = NULL) :m_data(data), m_pNext(pNext)
		{}
	};

	Node* pTop;
	size_t currSize;
};

template <class T>
Stack<T>::Stack():pTop(NULL),currSize(0) {}

template<class T>
inline Stack<T>::Stack(const Stack & rhs)
{
	copyFrom(rhs);
}

template<class T>
inline Stack<T> & Stack<T>::operator=(const Stack & rhs)
{
	if (this!=&rhs)
	{
		clean();
		copyFrom(rhs);
	}

	return *this;
}

template <class T>
Stack<T>::~Stack() 
{
	clean();
}

template <class T>
void Stack<T>::push(const T& data) 
{
	Node* newNode = new Node(data, pTop);
	pTop = newNode;

	currSize++;
}

template <class T>
void Stack<T>::pop() 
{
	if (isEmpty())
	{
		throw std::exception("the stack is empty!");
	}

	Node* destroy = pTop;
	pTop = pTop->m_pNext;

	delete destroy;
	currSize--;
}

template <class T>
T& Stack<T>::peek() 
{
	if (isEmpty())
	{
		throw std::exception("the stack is empty!");
	}

	return pTop->m_data;
}

template<class T>
const T& Stack<T>::peek() const
{
	if (isEmpty())
	{
		throw std::exception("the stack is empty!");
	}

	return pTop->m_data;
}

template<class T>
inline void Stack<T>::print() const
{
	Node* temp = pTop;
	while (temp)
	{
		std::cout << temp->m_data << ' ';
		temp = temp->m_pNext;
	}
	std::cout << std::endl;
}

template<class T>
inline void Stack<T>::copyFrom(const Stack & rhs)
{
	if (rhs.isEmpty())
		return;
	try
	{
		pTop = new Node(rhs.pTop->m_data);
		Node* copyFrom = rhs.pTop->m_pNext;
		Node* copyTo = pTop;
		while (copyFrom)
		{
			copyTo->m_pNext = new Node(copyFrom->m_data);
			copyFrom = copyFrom->m_pNext;
			copyTo = copyTo->m_pNext;
		}
	}
	catch (const std::bad_alloc& ba)
	{
		std::cout << ba.what();
		clean();
		throw;
	}
	

	currSize = rhs.currSize;
}

template<class T>
inline void Stack<T>::clean()
{
	Node* destroy;
	while (pTop)
	{
		destroy = pTop;
		pTop = pTop->m_pNext;
		delete destroy;
	}
	currSize = 0;
}
