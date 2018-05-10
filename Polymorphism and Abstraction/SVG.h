#pragma once
#include <string>
#include "DynamicArray.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

class SVG 
{
public:
	//prints all the figures in the screen
	void print()const;

	//creates a new figure by given attributes
	void createFigure();

	//erases a figure by given @index
	void eraseFigure(int index);

	//translates all or a certain figure
	void translate();

	//prints every figure if it is within the rectangle @r
	void withinRectangle(const Rectangle& r)const;

	//creates a figure from a given svg format @fileLine
	void createFromFile(char* fileLine);

	//saves every figure in a file by the svg format
	void saveFiguresInFile(std::fstream& file)const;

	~SVG();
private:
	//gets the color for a figure from a fileLine
	const char* getFileColor(const char* fileInfo);

private:
	DynamicArray<Figure*> figureContainer;
};
