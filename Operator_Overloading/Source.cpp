#include "Basket.h"

//saves the info of a basket in a text file
//with the name "report_'nameOfBasket'.txt"
void report(const Basket& b) 
{
	//constructing the file name
	//12 is used for the amount of symbols in "report_" and ".txt"
	char* fileName = new char[strlen(b.getOwner()) + 12];
	strcpy(fileName, "report_");
	strcat(fileName, b.getOwner());
	strcat(fileName, ".txt");

	//writing every egg from the basket in the text file
	std::ofstream out(fileName);
	for (int i = 0; i < b.getEggsAmount(); i++)
		out << b[i].getName() << ' ' << b[i].getSize() << '\n';

	delete[] fileName;
	out.close();
}

int main() 
{
	
	return 0;
}