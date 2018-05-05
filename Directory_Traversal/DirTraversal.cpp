#include "DirTraversal.h"

DirTraversal::DirTraversal():root(nullptr)
{}

DirTraversal::DirTraversal(const DirTraversal & rhs)
{
	copyFrom(rhs.root);
}

DirTraversal & DirTraversal::operator=(const DirTraversal & rhs)
{
	if (this != &rhs)
	{
		clear(root);
		copyFrom(rhs.root);
	}

	return *this;
}

DirTraversal::~DirTraversal()
{
	clear(root);
	remove("temp.dat");
}

void DirTraversal::extract(std::string path, const char * extension)
{
	getFiles(path, extension);
	printFilesDesc();
	clear(root);
	root = nullptr;
}

void DirTraversal::getFiles(const std::string& path, const char * extension)
{
	std::ofstream oFile("temp.dat", std::ios::binary);

	//this is used for file identificator
	unsigned fileCounter = 0;

	//stack for storing the file path and the access to
	//the other files and subdirectories
	std::pair<Stack<std::string>, Stack<HANDLE>> sh;

	std::string fPath(path);
	sh.first.push(fPath);
	fPath += "\\*";

	WIN32_FIND_DATA ffd;
	sh.second.push(FindFirstFile(fPath.c_str(), &ffd));

	do
	{
		//if the file is a directory push it in the stack 
		//and start searching in it
		if (ffd.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
		{
			if (strcmp(".", ffd.cFileName) != 0 && strcmp("..", ffd.cFileName) != 0)
			{
				sh.first.push(sh.first.peek() + "\\" + ffd.cFileName);

				std::string newDir(sh.first.peek() + "\\*");
				sh.second.push(FindFirstFile(newDir.c_str(), &ffd));
			}
		}
		//if it is a file
		else
		{
			//checks if the file name is valid by the given extension
			//and if thet is true the file data is inserted in the BST
			if (isValidFile(ffd.cFileName, extension))
			{
				std::string fullPath(sh.first.peek() + "\\" + ffd.cFileName);

				//saving the path of the file in a temporary file 
				oFile.write(fullPath.c_str(), MAX_PATH);

				insert(root, fileCounter++, ffd.nFileSizeLow);
			}
		}
		//if there are no more files in the current directory the files
		//from the current directory are being removed srom the stack
		while (!sh.second.isEmpty() && FindNextFile(sh.second.peek(), &ffd) == 0)
		{
			FindClose(sh.second.peek());
			sh.first.pop();
			sh.second.pop();
		}

	} while (!sh.first.isEmpty());

	oFile.close();
}

void DirTraversal::insert(Node*& root, unsigned fileID, unsigned fileSize)
{
	if (!root)
		root = new Node(fileID, fileSize);

	else
		(fileSize < root->fileSize) ? insert(root->leftChild, fileID, fileSize) : insert(root->rightChild, fileID, fileSize);
}

void DirTraversal::printFilesDesc()const
{
	Stack<Node*> s;
	std::ifstream iFile("temp.dat", std::ios::binary);

	Node* tempRoot = root;
	
	while (!s.isEmpty() || tempRoot != nullptr)
	{
		if (tempRoot)
		{
			s.push(tempRoot);
			tempRoot = tempRoot->rightChild;
		}
		else
		{
			char fullPath[MAX_PATH];
			iFile.seekg(s.peek()->fileId * MAX_PATH, std::ios::beg);
			iFile.read(fullPath, MAX_PATH);

			std::cout << fullPath << ' ' << s.peek()->fileSize << '\n';
			tempRoot = s.peek()->leftChild;
			s.pop();
		}
	}

	iFile.close();
}

bool DirTraversal::isValidFile(const char * fileName, const char * extension) const
{
	bool isChosen = true;
	int i = strlen(fileName) - strlen(extension);

	if (fileName[i - 1] != '.')
		isChosen = false;

	else
	{
		for (int j = 0; fileName[i] != '\0'; i++, j++)
		{
			if (fileName[i] != extension[j])
			{
				isChosen = false;
				break;
			}
		}
	}

	return isChosen;
}

void DirTraversal::clear(Node*& root)
{
	if (root)
	{
		clear(root->leftChild);
		clear(root->rightChild);
		delete root;
	}
}

DirTraversal::Node* DirTraversal::copyFrom(Node* root)
{
	if (!root)
		return nullptr;

	else
		return new Node(root->fileId, root->fileSize, copyFrom(root->leftChild), copyFrom(root->rightChild));
}
