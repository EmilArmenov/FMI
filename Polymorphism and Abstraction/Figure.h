#pragma once
#include "Point.h"
#include <fstream>

const int COLOR_LENGTH = 10;
const int MAX_INPUT_LENGTH = 128;

//class Figure needs to know about class Rectangle
//so that @within function can work properly
class Rectangle;

class Figure 
{
public:
	Figure(const char* color);
	Figure(const Figure& rhs);
	Figure& operator=(const Figure& rhs);
	virtual ~Figure();

public:
	//prints the information of a figure(attributes) on the screen
	virtual void print()const = 0;

	//translates all the points in a figure
	virtual void translate(double x, double y) = 0;

	//checks if a figure is in a given rectangle range
	virtual bool within(const Rectangle&rhs)const = 0;

	//saves the information of a figure(attributes) in a @file by the svg standart
	virtual void saveInFile(std::fstream& file)const = 0;

	//returns the type of a figure(rectangle, circle...)
	virtual const char* getFigType()const = 0;

private:
	//initializes the data member @color of a figure
	void init(const char* clr);

protected:
	const char* color;
};