#pragma once
#include "Figure.h"

//a rectangle is defined by a point, width, height and a color
class Rectangle :public Figure
{
public:
	Rectangle();
	Rectangle(Point p, double w, double h, const char* color);
	Rectangle(const Rectangle& rhs);
	Rectangle& operator=(const Rectangle& rhs);
	~Rectangle() {}

public:
	virtual void print()const;
	virtual void translate(double x, double y);
	virtual bool within(const Rectangle& rhs)const;
	virtual void saveInFile(std::fstream& file)const;
	virtual const char* getFigType()const;

public:
	//gets the point of the rectangle
	Point getPoint()const;

	//gets the width
	double getWidth()const;

	//gets the height
	double getHeight()const;

private:
	Point p1;
	double width;
	double height;
};
