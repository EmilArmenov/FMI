#include "LinkedList.h"

int main()
{
	LinkedList<int> ll;
	ll.insertFront(3);
	ll.insertBack(4);
	ll.insertBack(5);
	ll.insertBack(6);

	for (LinkedList<int>::Iterator it = ll.begin(); it != ll.end(); ++it) {
		if (*it == 4)
		{
			ll.eraseAfter(it);
		}
	}

	ll.insertBack(11);
	ll.print();

	return 0;
}