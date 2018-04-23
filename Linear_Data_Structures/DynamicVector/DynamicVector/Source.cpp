#include <iostream>
#include "DArray.h"

int main() 
{
	DynamicArray<int> d(5);
	d.add(1);
	d.add(2); d.add(3); d.add(11);
	d.add(2); d.add(5); d.add(11);
	DynamicArray<int> d4 (d);
	d4[3];
	d.print();
	d4.print();
	DynamicArray<int> d2;
	d2.add(100);
	d2.add(200);
	d2 += d4;
	d2.find(3);
	d2.removeBack();
	d2.removeBack();
	d2.remove(6);
	d2.insertAt(1, 15);
	d2.insertAt(7, 15);
	d2.print();

	int cArr[5] = { 1, 2, 3, 4, 5 };
	DynamicArray<int> d3(cArr, 10);
				
	return 0;		
}