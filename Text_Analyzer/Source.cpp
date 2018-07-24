#include "File_Analyzer.h"

int main() 
{
	File_Analyzer fa("dictionary.txt");
	std::cout << fa.analyzeFile("fact.txt") << "\n";
	
	return 0;
}