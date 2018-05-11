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
	virtual void print()const;
	virtual void translate(double x, double y);
	virtual bool within(const Rectangle& rhs)const;
	virtual void saveInFile(std::fstream& file)const;
	virtual const char* getFigType()const;
	virtual Line* clone() { return (new Line(*this)); }

private:
	Point p1, p2;
	double strokeWidth;
};
