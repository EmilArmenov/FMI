#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Stack.h"

/*This program finds all the files by the given extension in the given directory
and all its subdirectories. When a file with the wanted extension is found
it gets inserted in a BST with its size and some file ID and the file name is saved
in a temporary binary file. That's because the file names might consume too much memory if they
get stored in the tree. When the files need to be printed in descending order the file names
are being extracted from the temporary file. This happens in a constant time by getting the
position of the fileName with the file ID from the tree.A recursion is avoided
in @getFiles function because the directory tree might be too big and this might overflow the call stack.*/

class DirTraversal 
{
public:
	DirTraversal();
	DirTraversal(const DirTraversal& rhs);
	DirTraversal& operator=(const DirTraversal& rhs);
	~DirTraversal();

public:
	//only this function is needed for the outer world to extract the files
	//the private functions do the hard work
	void extract(std::string path, const char* extension);

private:
	struct Node
	{
		unsigned fileId;
		unsigned fileSize;
		Node* leftChild;
		Node* rightChild;

		Node(unsigned fileCounter, unsigned fSize, Node* left = nullptr, Node* right = nullptr):
			fileId(fileCounter), fileSize(fSize), leftChild(left), rightChild(right)
		{}
	};

	Node* root;

private:
	//extracts files from the given directory
	//@path - the path where the directory is 
	//@extension - which files to be extracted
	void getFiles(const std::string& path, const char* extension);

	//inserts the file size and ID in the BST
	void insert(Node*& root, unsigned fileID, unsigned fileSize);

	//prints the files in descending order by raversing
	//the tree (right - root - left)
	void printFilesDesc()const;

	//check if the extension given is the same as
	//the extension of the found file
	bool isValidFile(const char* fileName, const char* extension)const;
	
	//clears the BST
	void clear(Node*& root);

	//@root - root of another tree to copy his elements
	Node* copyFrom(Node* root);
};
