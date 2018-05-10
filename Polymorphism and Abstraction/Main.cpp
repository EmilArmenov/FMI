#include "Interface.h"

void commandReader() 
{
	Interface i;
	
	while (true)
	{
		char command[MAX_INPUT_LENGTH];
		std::cin >> command;

		if (strcmp(command, "open") == 0)
		{
			std::string filePath;
			std::cin >> filePath;
			i.open(filePath.c_str());
		}

		else if (strcmp(command, "close") == 0)
			i.close();

		else if (strcmp(command, "save") == 0)
			i.save();

		else if (strcmp(command,"create")==0)
			i.create();

		else if (strcmp(command, "print") == 0)
			i.print();

		else if (strcmp(command, "saveas") == 0)
		{
			std::string filePath;
			std::cin >> filePath;
			i.saveAs(filePath.c_str());
		}
		else if (strcmp(command, "erase") == 0)
			i.erase();
		
		else if (strcmp(command, "translate") == 0)
			i.translate();
		
		else if (strcmp(command, "within") == 0)
			i.within();
		
		else if (strcmp(command, "exit") == 0)
			return;

		else
			std::cout << "Command Unknown... \n";
	}
}

int main() 
{
	commandReader();

	return 0;
}