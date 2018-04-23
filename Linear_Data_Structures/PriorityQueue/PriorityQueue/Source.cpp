#include "PriorityQueue.h"

int main() 
{
	PriorityQueue<int> p;
	int a = 2;
	p.push(1);
	p.push(12);
	p.push(9);
	p.push(5);
	p.push(6);
	p.push(10);
	for (int i = 0; i < 6; i++)
	{
		std::cout << p.top() <<  ' ';
		p.pop();
	}
	
	return 0;
}