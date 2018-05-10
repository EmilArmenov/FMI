#pragma once
#include "SVG.h"

class Interface 
{
public:
	Interface() {};
	void open(const char* path);
	void close();
	void save();
	void saveAs(const char* path);

	void create();
	void print()const;
	void erase();
	void translate();
	void within()const;
	~Interface();

private:
	//gets the position from the given @path where the file name starts
	int getFileNamePos(const char* path)const;

private:
	//forbidden functions just because
	Interface(const Interface& rhs) = delete;
	Interface& operator=(const Interface& rhs) = delete;

private:
	//stores the figures created from a file or by the user
	SVG figures;

	//reads and writes this @file
	std::fstream file;

	//stores the file name
	std::string fileName;

	//stores the full path to a given file
	std::string filePath;
};
