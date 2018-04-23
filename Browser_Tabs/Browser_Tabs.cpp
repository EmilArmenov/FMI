#include "Browser_Tabs.h"

BrowserTab::BrowserTab() :currTab{ new Tab("about:blank") }, pBeg(currTab)
{
}

BrowserTab::BrowserTab(const BrowserTab & rhs)
{
	copyFrom(rhs);
}

BrowserTab & BrowserTab::operator=(const BrowserTab & rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}

	return *this;
}

BrowserTab::~BrowserTab()
{
	clear();
}

void BrowserTab::go(const char* newURL)
{
	delete[]currTab->url;
	currTab->url = new char[strlen(newURL) + 1];
	strcpy(currTab->url, newURL);
	currTab->timeStamp = time(NULL);
}

void BrowserTab::insert(const char* newURL)
{
	Tab* newTab = new Tab(newURL);

	// if new tab is inserted after the last one
	if (currTab->pNext == NULL)
	{
		currTab->pNext = newTab;
		newTab->pPrev = currTab;
	}
	// if new tab is inserted between two others
	else
	{
		newTab->pNext = currTab->pNext;
		currTab->pNext->pPrev = newTab;
		newTab->pPrev = currTab;
		currTab->pNext = newTab;
	}

	currTab = newTab;
}

void BrowserTab::back()
{
	if (currTab->pPrev == NULL)
		return;

	currTab = currTab->pPrev;
}

void BrowserTab::forward()
{
	if (currTab->pNext == NULL)
		return;

	currTab = currTab->pNext;
}

void BrowserTab::remove()
{
	Tab* destroy = currTab;

	// if there is only one tab
	if (currTab->pNext == NULL && currTab->pPrev == NULL)
	{
		Tab* newTab = new Tab("about:blank");
		pBeg = currTab = newTab;
	}
	// if the first tab is deleted
	else if (currTab == pBeg)
	{
		pBeg = currTab = currTab->pNext;
		currTab->pPrev = NULL;
	}
	// if a tab in the middle is deleted
	else if (currTab->pNext != NULL)
	{
		currTab->pNext->pPrev = currTab->pPrev;
		currTab->pPrev->pNext = currTab->pNext;
		currTab = currTab->pNext;
	}
	// if the last tab is deleted
	else
	{
		currTab = currTab->pPrev;
		currTab->pNext = NULL;
	}

	delete destroy;
}

void BrowserTab::print() const
{
	Tab* printer = pBeg;

	while (printer)
	{
		if (printer == currTab)
			std::cout << '>';

		std::cout << printer->url << ' ' << printer->timeStamp << '\n';
		printer = printer->pNext;
	}
}

void BrowserTab::clear()
{
	Tab* toDestroy = pBeg;

	while (pBeg)
	{
		pBeg = pBeg->pNext;
		delete toDestroy;
		toDestroy = pBeg;
	}

	currTab = NULL;
}

void BrowserTab::copyFrom(const BrowserTab & rhs)
{
	try
	{
		Tab* copyToTab = new Tab(rhs.pBeg->url, rhs.pBeg->timeStamp);
		pBeg = copyToTab;

		if (rhs.currTab == rhs.pBeg)
			currTab = pBeg;

		Tab* copyFromTab = rhs.pBeg->pNext;

		while (copyFromTab)
		{
			copyToTab->pNext = new Tab(copyFromTab->url, copyFromTab->timeStamp);
			copyToTab->pNext->pPrev = copyToTab;
			copyToTab = copyToTab->pNext;

			if (rhs.currTab == copyFromTab)
				currTab = copyToTab;

			copyFromTab = copyFromTab->pNext;
		}
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "No memory left!" << '\n';
		clear();
		throw;
	}
}

void BrowserTab::sortBy(const char * what)
{
	if (strcmp(what, "URL") == 0)
		mergeByURL(&pBeg);

	else if (strcmp(what, "TIME") == 0)
		mergeByTIME(&pBeg);

	else
	{
		std::cout << "No such command" << '\n';
		return;
	}

	currTab = pBeg;
}

void BrowserTab::mergeByURL(Tab** headRef)
{
	Tab* head = *headRef;
	if (!head || !head->pNext)
		return;

	// splits the list in the middle
	Tab *secondHalf = split(head);

	// recursevly splitting the left and the right halves
	mergeByURL(&head);
	mergeByURL(&secondHalf);

	// merge the sorted halves
	// headRef points at the begining of the returned list
	*headRef = mergeSortedURL(head, secondHalf);
}

void BrowserTab::mergeByTIME(Tab** headRef)
{
	Tab* head = *headRef;
	if (!head || !head->pNext)
		return;

	// splits the list in the middle
	Tab *secondHalf = split(head);

	// recursevly splitting the left and the right halves
	mergeByTIME(&head);
	mergeByTIME(&secondHalf);

	// merge the sorted halves
	// headRef points at the begining of the returned list
	*headRef = mergeSortedTIME(head, secondHalf);
}

BrowserTab::Tab* BrowserTab::split(Tab* head)
{
	Tab *fast = head, *slow = head;

	//when fast ptr reaches the end of the list
	//slow ptr will be at the middle
	while (fast->pNext && fast->pNext->pNext)
	{
		fast = fast->pNext->pNext;
		slow = slow->pNext;
	}

	Tab *temp = slow->pNext;
	slow->pNext = NULL;
	return temp;
}

BrowserTab::Tab* BrowserTab::mergeSortedURL(Tab* leftHalf, Tab* rightHalf)
{
	if (!leftHalf)
		return rightHalf;

	if (!rightHalf)
		return leftHalf;

	Tab* sortingPtr;

	// choose where to put sortingPtr as a starting position of the list
	// depends on which starting pos of the two lists is smaller
	if (strcmp(leftHalf->url, rightHalf->url) < 0)
	{
		sortingPtr = leftHalf;
		leftHalf = leftHalf->pNext;
	}
	else if (strcmp(leftHalf->url, rightHalf->url) > 0)
	{
		sortingPtr = rightHalf;
		rightHalf = rightHalf->pNext;
	}
	else
	{
		if (leftHalf->timeStamp <= rightHalf->timeStamp)
		{
			sortingPtr = leftHalf;
			leftHalf = leftHalf->pNext;
		}
		else
		{
			sortingPtr = rightHalf;
			rightHalf = rightHalf->pNext;
		}
	}

	Tab* newList = sortingPtr;  // newList will point at the beggining of the returned list

	// merges the two halves in sorted order
	while (leftHalf && rightHalf)
	{
		if (strcmp(leftHalf->url, rightHalf->url) < 0)
		{
			sortingPtr->pNext = leftHalf;
			sortingPtr = leftHalf;
			leftHalf = leftHalf->pNext;
		}
		else if (strcmp(leftHalf->url, rightHalf->url) > 0)
		{
			sortingPtr->pNext = rightHalf;
			sortingPtr = rightHalf;
			rightHalf = rightHalf->pNext;
		}
		else
		{
			if (leftHalf->timeStamp <= rightHalf->timeStamp)
			{
				sortingPtr->pNext = leftHalf;
				sortingPtr = leftHalf;
				leftHalf = leftHalf->pNext;
			}
			else
			{
				sortingPtr->pNext = rightHalf;
				sortingPtr = rightHalf;
				rightHalf = rightHalf->pNext;
			}
		}
	}

	if (leftHalf == NULL) sortingPtr->pNext = rightHalf;
	if (rightHalf == NULL) sortingPtr->pNext = leftHalf;

	return newList;
}

BrowserTab::Tab* BrowserTab::mergeSortedTIME(Tab* leftHalf, Tab* rightHalf)
{
	if (!leftHalf)
		return rightHalf;

	if (!rightHalf)
		return leftHalf;

	Tab* sortingPtr;

	// choose where to put sortingPtr as a starting position of the list
	// depends on which starting pos of the two lists is smaller
	if (leftHalf->timeStamp < rightHalf->timeStamp)
	{
		sortingPtr = leftHalf;
		leftHalf = leftHalf->pNext;
	}
	else if (leftHalf->timeStamp > rightHalf->timeStamp)
	{
		sortingPtr = rightHalf;
		rightHalf = rightHalf->pNext;
	}
	else
	{
		if (strcmp(leftHalf->url, rightHalf->url) <= 0)
		{
			sortingPtr = leftHalf;
			leftHalf = leftHalf->pNext;
		}
		else
		{
			sortingPtr = rightHalf;
			rightHalf = rightHalf->pNext;
		}
	}

	Tab* newList = sortingPtr;  // newList will point at the beggining of the returned list

	// merges the two halves in sorted order
	while (leftHalf && rightHalf)
	{
		if (leftHalf->timeStamp < rightHalf->timeStamp)
		{
			sortingPtr->pNext = leftHalf;
			sortingPtr = leftHalf;
			leftHalf = leftHalf->pNext;
		}
		else if (leftHalf->timeStamp > rightHalf->timeStamp)
		{
			sortingPtr->pNext = rightHalf;
			sortingPtr = rightHalf;
			rightHalf = rightHalf->pNext;
		}
		else
		{
			if (strcmp(leftHalf->url, rightHalf->url) <= 0)
			{
				sortingPtr->pNext = leftHalf;
				sortingPtr = leftHalf;
				leftHalf = leftHalf->pNext;
			}
			else
			{
				sortingPtr->pNext = rightHalf;
				sortingPtr = rightHalf;
				rightHalf = rightHalf->pNext;
			}
		}
	}

	if (leftHalf == NULL) sortingPtr->pNext = rightHalf;
	if (rightHalf == NULL) sortingPtr->pNext = leftHalf;

	return newList;
}