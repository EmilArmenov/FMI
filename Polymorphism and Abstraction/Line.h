#pragma once
#include "Figure.h"
#include "Rectangle.h"

//a line is defined by two points, stroke of the line and a color
class Line :public Figure
{
public:
	Line();
	Line(Point, Point, double stroke, const char* color);
	Line(const Line& rhs);
	Line&operator=(const Line& rhs);
	~Line() {}

public:
	void print()const;
	void translate(double x, double y);
	bool within(const Rectangle& rhs)const;
	void saveInFile(std::fstream& file)const;
	const char* getFigType()const;

private:
	Point p1, p2;
	double strokeWidth;
};
