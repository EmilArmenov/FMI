#include "SVG.h"

void SVG::createFigure()
{
	//to see what type of figure the user wants
	std::string figName;
	std::cin >> figName;

	std::string color;

	if (figName == "rectangle")
	{
		double x, y, width, height;
		std::cin >> x;
		std::cin >> y;
		std::cin >> width;
		std::cin >> height;
		std::cin >> color;
		figureContainer.add(new Rectangle(Point(x, y), width, height, color.c_str()));
		std::cout << "succesfully created a rectangle " << figureContainer.getSize() << std::endl;
	}
	else if (figName == "circle")
	{
		double x, y, radius;
		std::cin >> x;
		std::cin >> y;
		std::cin >> radius;
		std::cin >> color;
		figureContainer.add(new Circle(Point(x, y), radius, color.c_str()));
		std::cout << "succesfully created a circle " << figureContainer.getSize() << std::endl;
	}
	else if (figName == "line")
	{
		double x1, y1, x2, y2, stroke;
		std::cin >> x1;
		std::cin >> y1;
		std::cin >> x2;
		std::cin >> y2;
		std::cin >> stroke;
		std::cin >> color;
		figureContainer.add(new Line(Point(x1, y1), Point(x2, y2), stroke, color.c_str()));
		std::cout << "succesfully created a line " << figureContainer.getSize() << std::endl;
	}
	else 
	{
		std::cout << "Unknown figure \n";
		return;
	}
}

//really messy function for reading figures from a file line
//gets every interval sapareted word from the @fileLine and gets the wanted attributes at the certain position
//it is important for "=" sign in the @fileLine not to be space separated
void SVG::createFromFile(char * fileLine)
{
	char * pch;
	pch = strtok(fileLine, " ");

	//rectangle example: <rect x="5" y="5" width="10" height="10" fill="green" />
	if (strcmp(pch, "<rect") == 0)
	{
		double x, y, width, height;
		pch = strtok(NULL, " ");
		x = atoi(&pch[3]);
		pch = strtok(NULL, " ");
		y = atoi(&pch[3]);
		pch = strtok(NULL, " ");
		width = atoi(&pch[7]);
		pch = strtok(NULL, " ");
		height = atoi(&pch[8]);
		pch = strtok(NULL, " ");

		figureContainer.add(new Rectangle(Point (x, y), width, height, getFileColor(pch)));
	}
	//circle example: <circle cx="5" cy="5" r="10" fill="blue" />
	else if (strcmp(pch, "<circle") == 0)
	{
		double x, y, radius;
		pch = strtok(NULL, " ");
		x = atoi(&pch[4]);
		pch = strtok(NULL, " ");
		y = atoi(&pch[4]);
		pch = strtok(NULL, " ");
		radius = atoi(&pch[3]);
		pch = strtok(NULL, " ");

		figureContainer.add(new Circle(Point (x, y), radius, getFileColor(pch)));
	}

	//line example <line x1="100" y1="300" x2="300" y2="100" stroke-width="5" stroke="green" />
	else if (strcmp(pch, "<line") == 0)
	{
		double x1, y1, x2, y2, stroke;
		pch = strtok(NULL, " ");
		x1 = atoi(&pch[4]);
		pch = strtok(NULL, " ");
		x2 = atoi(&pch[4]);
		pch = strtok(NULL, " ");
		y1 = atoi(&pch[4]);
		pch = strtok(NULL, " ");
		y2 = atoi(&pch[4]);
		pch = strtok(NULL, " ");
		stroke = atoi(&pch[14]);
		pch = strtok(NULL, " ");

		figureContainer.add(new Line(Point(x1, y1), Point(x2, y2), stroke, getFileColor(pch)));
	}
}

SVG::SVG(const SVG & rhs)
{
	for (int i = 0; i < rhs.figureContainer.getSize(); i++)
		figureContainer.add(rhs.figureContainer[i]->clone());
}

SVG & SVG::operator=(const SVG & rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < figureContainer.getSize(); i++)
			delete[] figureContainer[i];

		for (int i = 0; i < rhs.figureContainer.getSize(); i++)
			figureContainer.add(rhs.figureContainer[i]->clone());
	}
	return *this;
}

SVG::~SVG()
{
	for (int i = 0; i < figureContainer.getSize(); i++)
		delete[] figureContainer[i];
}

void SVG::saveFiguresInFile(std::fstream & file) const
{
	for (int i = 0; i < figureContainer.getSize(); i++)
		figureContainer[i]->saveInFile(file);
}

//@fileInfo can be stroke="..." for a line or fill="..." for the other figures
const char* SVG::getFileColor(const char * fileInfo)
{
	char *color = new char[COLOR_LENGTH];
	for (int i = 0; fileInfo[i] != '\0'; i++)
	{
		if (fileInfo[i] == '\"')
		{
			int j;
			i++;
			//puts the color in to the @color variable 
			for (j = 0; fileInfo[i] != '\"'; j++, i++)
				color[j] = fileInfo[i];

			color[j] = '\0';
			break;
		}
	}

	return color;
}

void SVG::eraseFigure(int index)
{
	try
	{
		//index - 1 is used in order to adjust the given @index with the array index
		std::cout << "Erased a " << figureContainer[index - 1]->getFigType() << " (" << index << ") \n";
		figureContainer.remove(index - 1);
	}
	catch (const std::out_of_range&)
	{
		std::cout << "There is no figure number " << index << "! \n";
	}
}

//really messy function for translating the figures
//it is dangerous to play with fire so it won't be touched anymore
void SVG::translate()
{
	char input[MAX_INPUT_LENGTH];
	double x, y;

	std::cin.getline(input, MAX_INPUT_LENGTH, '=');

	int i = 0;
	while (input[i] == ' ')
		i++;

	int num;
	bool oneFig = false;
	if (input[i] >= '0' && input[i] <= '9') 
	{
		num = atoi(&input[i]);
		oneFig = true;
		while (input[i] != ' ')
			i++;
	}

	if (oneFig)
	{
		if (strcmp(input + i, " vertical") == 0)
			std::cin >> y;
		else
		{
			std::cout << "unknown command \n";
			return;
		}

		std::cin.getline(input, MAX_INPUT_LENGTH, '=');

		if (strcmp(input, " horizontal") == 0)
			std::cin >> x;
		else
		{
			std::cout << "unknown command \n";
			return;
		}

		try
		{
			std::cout << "Translated " << figureContainer[num - 1]->getFigType() << " (" << num << ") \n";
			figureContainer[num-1]->translate(x, y);
		}
		catch (const std::out_of_range&)
		{
			std::cout << "There is no figure number " << num << "! \n";
		}
	}
	else
	{
		if (strcmp(input, " vertical") == 0)
			std::cin >> y;
		else
		{
			std::cout << "unknown command \n";
			return;
		}

		std::cin.getline(input, MAX_INPUT_LENGTH, '=');

		if (strcmp(input, " horizontal") == 0)
			std::cin >> x;
		else
		{
			std::cout << "unknown command \n";
			return;
		}

		for (int i = 0; i < figureContainer.getSize(); i++)
			figureContainer[i]->translate(x, y);
		std::cout << "Translated all figures" << std::endl;
	}
}

void SVG::withinRectangle(const Rectangle& r) const
{
	for (int i = 0; i < figureContainer.getSize(); i++)
	{
		if (figureContainer[i]->within(r))
			figureContainer[i]->print();
	}
}

void SVG::print()const
{
	if (figureContainer.getSize() <= 0)
	{
		std::cout << "No figures to print!" << std::endl;
		return;
	}

	for (int i = 0; i < figureContainer.getSize(); i++)
	{
		std::cout << i + 1 << ". ";
		figureContainer[i]->print();
	}
}
