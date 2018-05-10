#include "Interface.h"

Interface::~Interface()
{
	if (file.is_open())
	{
		file.clear();
		file.close();
	}
}

void Interface::open(const char * path)
{
	file.open(path, std::ios::in);

	if (file.is_open())
	{
		filePath = path;
		fileName = path + getFileNamePos(path);
		std::cout << "Successfully opened " << fileName << std::endl;

		std::string line;
		while (getline(file, line))
		{
			if (strcmp(line.c_str(), "<svg>") == 0)
				break;
		}
		while (getline(file, line))
		{
			if (strcmp(line.c_str(), "</svg>") == 0)
				break;

			figures.createFromFile((char*)line.c_str());
		}
	}
	else
		std::cout << "Something went wrong with the file \n";
}

void Interface::close()
{
	if (file.is_open())
	{
		file.close();
		std::cout << "Successfully closed " << fileName << std::endl;
	}
	else
		std::cout << "You have to open a file first \n";
}

void Interface::save()
{
	if (file.is_open())
		saveAs(filePath.c_str());
	
	else
		std::cout << "You have to open a file first \n";
}

void Interface::saveAs(const char * path)
{
	std::fstream saveFile(path, std::ios::out);

	saveFile << "<?xml version=\"1.0\" standalone=\"no\"?>" << std::endl;
	saveFile << " <!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"" << std::endl;
	saveFile << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/" << "\">" << std::endl;
	saveFile << "<svg>" << std::endl;

	figures.saveFiguresInFile(saveFile);

	saveFile << "</svg>" << std::endl;

	std::cout << "Succesfully saved changes to " << path + getFileNamePos(path) << std::endl;
}

void Interface::create()
{
	figures.createFigure();
}

void Interface::print() const
{
	figures.print();
}

void Interface::erase()
{
	int index;
	std::cin >> index;
	figures.eraseFigure(index);
}

void Interface::translate()
{
	figures.translate();
}

void Interface::within() const
{
	std::string figure;
	std::cin >> figure;

	if (figure == "rectangle")
	{
		double x, y, width, height;
		std::cin >> x;
		std::cin >> y;
		std::cin >> width;
		std::cin >> height;
		
		Rectangle r(Point (x, y), width, height, "black");
		figures.withinRectangle(r);
	}
	else
		std::cout << "Can't check this figure \n";
}

int Interface::getFileNamePos(const char* filePath) const
{
	int i = strlen(filePath);
	while (filePath[i] != '\\' && i >= 0)
		i--;

	return i + 1;
}
