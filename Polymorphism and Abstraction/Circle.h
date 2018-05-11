#pragma once
#include "Figure.h"
#include "Rectangle.h"

//a circle is defined by a point(center) and a radius
class Circle : public Figure
{
public:
	Circle();
	Circle(Point p_1, double radius, const char* color);
	Circle(const Circle& rhs);
	Circle&operator=(const Circle& rhs);
	~Circle() {}

public:
	void print()const;
	void translate(double x, double y);
	bool within(const Rectangle& rhs)const;
	void saveInFile(std::fstream& file)const;
	const char* getFigType()const;
	virtual Circle* clone() { return (new Circle(*this)); }

private:
	Point center;
	double radius;
};
