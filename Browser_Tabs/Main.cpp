#include "Browser_Tabs.h"

const short MAX_URL_LENGTH = 1024;
const short MAX_COMMAND_LENGTH = 10;

void commandReader() 
{
	BrowserTab BT;
	while (true)
	{
		char command[MAX_COMMAND_LENGTH];
		std::cin >> command;
		char what[MAX_URL_LENGTH];

		if (strcmp(command, "GO") == 0)
		{
			std::cin >> what;
			BT.go(what);
		}
		else if (strcmp(command, "INSERT") == 0)
		{
			std::cin >> what;
			BT.insert(what);
		}
		else if (strcmp(command, "BACK") == 0)
		{
			BT.back();
		}
		else if (strcmp(command, "FORWARD") == 0)
		{
			BT.forward();
		}
		else if (strcmp(command, "REMOVE") == 0)
		{
			BT.remove();
		}
		else if (strcmp(command, "PRINT") == 0)
		{
			BT.print();
		}
		else if (strcmp(command, "SORT") == 0)
		{
			std::cin >> what;
			BT.sortBy(what);
		}

		else break;
	}
}

int main() 
{
	commandReader();

	return 0;
}