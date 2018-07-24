#pragma once
#include "Trie.h"

class File_Analyzer 
{
public:
	File_Analyzer(const std::string& fileDictionary);
	~File_Analyzer();
	double analyzeFile(const std::string& file);

private:
	void openFile(const std::string& file);

private:
	File_Analyzer(const File_Analyzer& rhs) = delete;
	File_Analyzer& operator=(const File_Analyzer& rhs) = delete;

private:
	std::ifstream rFile;
	Trie dictionary;
};
