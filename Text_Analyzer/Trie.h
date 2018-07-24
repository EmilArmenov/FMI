#pragma once

#include <iostream>
#include <string>
#include <fstream>

class Trie
{
public:
	Trie();
	~Trie();
	
	void createTrie(const std::string& fileDictionary);
	int rateWord(const std::string& word);

private:
	static const int max_known_symbols = 28;
	static const int spacebar_symbol = 27;
	struct trieNode
	{
		char symbol;
		bool endOfWord;
		int rating;
		trieNode *trieNext[max_known_symbols];

		trieNode(const char s = '$', bool eow = false, int r = 0) :symbol(s), endOfWord(eow), rating(r)
		{
			for (int i = 0; i < max_known_symbols; i++)
				trieNext[i] = nullptr;
		}
	};

private:
	trieNode* root;
	trieNode* iterator;

private:
	bool isValidWordSymbol(const char symbol);
	void addWord(const std::string& phrase, int score);
	void clearTrie(trieNode* root);
};