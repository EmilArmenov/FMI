#include "Trie.h"

Trie::Trie() :root(new trieNode), iterator(root)
{}

Trie::~Trie()
{
	clearTrie(root);
}

void Trie::createTrie(const std::string & fileDictionary)
{
	std::ifstream file(fileDictionary);
	if (!file)
		throw std::runtime_error("Couldn't open the file");

	std::string phrase;
	int score;

	while (std::getline(file, phrase, '\t'))
	{
		file >> score;
		addWord(phrase, score);
		file.get();
	}

	file.close();
}

bool Trie::isValidWordSymbol(const char symbol)
{
	return ((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z')) ? true : false;
}

void Trie::addWord(const std::string & phrase, int score)
{
	for (auto i = phrase.begin(); i != phrase.end(); ++i)
	{
		if ((*i) == ' ' || ((*i) >= 'a' && (*i) <= 'z'))
		{
			int wordPos = ((*i) == ' ') ? spacebar_symbol : (*i) - 'a';
			if (!iterator->trieNext[wordPos])
				iterator->trieNext[wordPos] = new trieNode((*i));

			iterator = iterator->trieNext[wordPos];
		}
		else
			break;
	}
	iterator->endOfWord = true;
	iterator->rating = score;
	iterator = root;
}

int Trie::rateWord(const std::string & word)
{
	bool isPrefix = true;
	for (auto i = word.begin(); i != word.end(); ++i)
	{
		if (!isValidWordSymbol((*i)))
			break;

		int wordPos = ((*i) >= 'A' && (*i) <= 'Z') ? ((*i) + ' ') - 'a' : (*i) - 'a';
		if (iterator->trieNext[wordPos])
			iterator = iterator->trieNext[wordPos];
		else if (isPrefix && root->trieNext[wordPos])
		{
			iterator = root->trieNext[wordPos];
			isPrefix = false;
		}
		else
		{
			iterator = root;
			return 0;
		}
	}

	if (iterator->endOfWord)
	{
		if (iterator->trieNext[spacebar_symbol])
		{
			iterator = iterator->trieNext[spacebar_symbol];
			return 0;
		}
		int rating = iterator->rating;
		iterator = root;
		return rating;
	}
	else if (iterator->trieNext[spacebar_symbol])
	{
		iterator = iterator->trieNext[spacebar_symbol];
		return 0;
	}
	else
	{
		iterator = root;
		return 0;
	}
}

void Trie::clearTrie(trieNode * root)
{
	if (root)
	{
		for (int i = 0; i < max_known_symbols; i++)
			clearTrie(root->trieNext[i]);

		delete root;
	}
}