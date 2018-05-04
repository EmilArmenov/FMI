#pragma once
#include <iostream>
#include <algorithm>

template <class T>
class BST 
{
public:
	BST();
	BST(const BST& otherTree);
	BST& operator=(const BST& otherTree);
	~BST();

	//in order to prevent exposing the root data member when called
	//the functions below have private implementations where the root can be given safely
	//as a parameter for the recursive calls
public:
	//inserts a new node in the tree
	//nodes with the same data are given to the right child
	void insert(const T& data) { insert(root, data); }

	//finds if @key exists in the tree
	bool find(const T& key)const { return find(root, key); }

	//removes a node from the tree 
	void remove(const T& key) { remove(root, key); }

	//prints the nodes in the tree (left - parent - right)
	void inorder()const { printInorder(root); }

	void visualInorder()const { printVisual(root); std::cout << std::endl; }

	//gets the height of the tree
	int height()const { return treeHeight(root); }

	//checks if the tree is balanced(a tree is balanced when)
	//the left and right subtrees' heights differ by at most one, and
	//the left subtree is balanced, and
	//the right subtree is balanced
	bool isBalanced()const { return isBalanced(root); }

private:
	struct node
	{
		T data;
		node *leftChild, *rightChild;

		node(const T& _data, node* _leftChild = nullptr, node* _rightChild = nullptr) : 
			data(_data), leftChild(_leftChild), rightChild(_rightChild)
		{}
	};

	node* root;

private:
	node* copy(node* root) 
	{
		if (!root)
			return nullptr;
		
		else 
			return new node(root->data, copy(root->leftChild), copy(root->rightChild));
	}

	//deletes the whole tree
	void clear(node* root) 
	{
		if (root)
		{
			clear(root->leftChild);
			clear(root->rightChild);
			delete root;
		}
	}

	node* findMin(node*& root)
	{
		//going through the left branch until a leaf is found
		if (root->leftChild)
			return findMin(root->leftChild);

		//getting the smallest node found
		node* smallest = root;
		//removing the duplicate of the smallest node
		root = root->rightChild;

		return smallest;
	}

private:
	void insert(node*& root, const T& data);
	bool find(const node* root, const T& key)const;
	void remove(node*& root, const T& key);
	void printInorder(const node* root)const;
	void printVisual(const node* root)const;
	int treeHeight(node* root)const;
	bool isBalanced(const node* root)const;
};

template<class T>
inline BST<T>::BST(): root(nullptr)
{}

template<class T>
inline BST<T>::BST(const BST & otherTree): root(copy(otherTree.root))
{}

template<class T>
inline BST<T> & BST<T>::operator=(const BST & otherTree)
{
	if (this != &otherTree)
	{
		clear(root);
		root = copy(otherTree.root);
	}
	return *this;
}

template<class T>
inline BST<T>::~BST()
{	
	clear(root); 
}

template<class T>
inline void BST<T>::insert(node *& root, const T & data)
{
	if (!root)
		root = new node(data);
	
	else 
		(data < root->data) ? insert(root->leftChild, data) : insert(root->rightChild, data);
}

template<class T>
inline bool BST<T>::find(const node * root, const T & key) const
{
	if (!root)
		return false;

	if (key == root->data)
		return true;

	else
	return (key < root->data) ? find(root->leftChild, key) : find(root->rightChild, key);
}

template<class T>
inline void BST<T>::remove(node *& root, const T & key)
{
	if (!root)
	{
		std::cout << "Couldn't find " << key << " in the tree \n";
		return;
	}

	if (root->data == key)
	{	
		//if the node is a leaf
		if (!root->leftChild&&!root->rightChild)
		{
			delete root;
			root = nullptr;
			return;
		}
		node* destroy = root;

		//if the node has only right child
		if (!root->leftChild)
			root = root->rightChild;
		
		//if the node has only left child
		else if (!root->rightChild)
			root = root->leftChild;
		
		//if the node has both children
		else
		{
			//finds the smallest element in the right subtree
			//the found element becomes the new parent
			node* minElement = findMin(root->rightChild);

			minElement->leftChild = root->leftChild;
			minElement->rightChild = root->rightChild;
			root = minElement;
		}
		delete destroy;
	}

	else
		remove((key < root->data) ? root->leftChild : root->rightChild, key);
}

template<class T>
inline void BST<T>::printInorder(const node * root) const
{
	if (root)
	{
		printInorder(root->leftChild);
		std::cout << root->data << '\n';
		printInorder(root->rightChild);
	}
}

template<class T>
inline void BST<T>::printVisual(const node * root) const
{
	if (!root)
		return;
	
	else
	{
		if (root->leftChild)
			std::cout << '(';
		
		printVisual(root->leftChild);

		if (!root->leftChild&&!root->rightChild)
			std::cout << "( - " << root->data << " - )";
		
		else if (root->leftChild&&!root->rightChild)
			std::cout << ' ' << root->data << " - )";
		
		else if (!root->leftChild&&root->rightChild)
			std::cout << "( - " << root->data << ' ';
		
		else
			std::cout << ' ' << root->data << ' ';
		
		printVisual(root->rightChild);

		if (root->rightChild)
			std::cout << ')';
	}
}

template<class T>
inline int BST<T>::treeHeight(node * root) const
{
	if (!root)
		return 0;
	
	else
	{
		int leftHeight = treeHeight(root->leftChild);
		int rightHeight = treeHeight(root->rightChild);
		
		//returns the bigger height between the left and the right subtree + 1 for the root
		return std::max(leftHeight, rightHeight) + 1;
	}
}

template<class T>
inline bool BST<T>::isBalanced(const node * root) const
{
	if (!root)
		return true;

	else
	{
		return ((abs(treeHeight(root->leftChild) - treeHeight(root->rightChild)) <= 1) &&
			isBalanced(root->leftChild) && isBalanced(root->rightChild));
	}
}
