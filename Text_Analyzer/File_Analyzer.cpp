#include "File_Analyzer.h"

File_Analyzer::File_Analyzer(const std::string & fileDictionary)
{
	dictionary.createTrie(fileDictionary);
}

File_Analyzer::~File_Analyzer()
{
	rFile.close();
}

void File_Analyzer::openFile(const std::string & file)
{
	if (rFile.is_open())
		rFile.close();
	
	rFile.open(file);

	if (!rFile)
		throw std::runtime_error("Couldn't open the file");
}

double File_Analyzer::analyzeFile(const std::string& file)
{
	openFile(file);
	std::string word;
	int wordCounter = 0, sum = 0;

	while (rFile>>word)
	{
		wordCounter++;
		sum += dictionary.rateWord(word);
	}

	return static_cast<double>(sum) / wordCounter;
}
