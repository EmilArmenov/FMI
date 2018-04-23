#pragma once
#include <iostream>
#include <ctime>

class BrowserTab
{
public:
	BrowserTab();
	BrowserTab(const BrowserTab& rhs);
	BrowserTab&operator=(const BrowserTab& rhs);
	~BrowserTab();

public:
	void go(const char* newURL);
	void insert(const char* newURL);
	void back();
	void forward();
	void remove();
	void print()const;

private:
	void clear();
	void copyFrom(const BrowserTab& rhs);

private:
	struct Tab
	{
		char* url;
		time_t timeStamp;
		Tab* pNext;
		Tab* pPrev;

		Tab(const char* newURL) :url(new char[strlen(newURL) + 1]), timeStamp(time(NULL)), pNext(NULL), pPrev(NULL)
		{
			strcpy(url, newURL);
		}

		Tab(const char* newURL, time_t t) :url(new char[strlen(newURL) + 1]), timeStamp(t), pNext(NULL), pPrev(NULL)
		{
			strcpy(url, newURL);
		}

		~Tab() { delete[] url; }
	};

	Tab* currTab;
	Tab* pBeg;

public:
	void sortBy(const char* what);
	
private:
	void mergeByURL(Tab** headRef);
	void mergeByTIME(Tab** headRef);

	Tab* split(Tab* head);
	
	Tab* mergeSortedURL(Tab* firstHalf, Tab* secondHalf);
	Tab* mergeSortedTIME(Tab* firstHalf, Tab* secondHalf);
};