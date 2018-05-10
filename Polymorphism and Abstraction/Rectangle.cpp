#include "Rectangle.h"

Rectangle::Rectangle() :p1(0, 0), width(0.0), height(0.0), Figure("white")
{}

Rectangle::Rectangle(Point p_1, double w, double h, const char* color) : Figure(color), p1(p_1), width(w), height(h)
{}

Rectangle::Rectangle(const Rectangle & rhs) : Figure(rhs), p1(rhs.p1), width(rhs.width), height(rhs.height)
{}

Rectangle & Rectangle::operator=(const Rectangle & rhs)
{
	if (this!=&rhs)
	{
		Figure::operator=(rhs);
		p1 = rhs.p1;
		width = rhs.width;
		height = rhs.height;
	}
	return *this;
}

void Rectangle::print() const
{
	std::cout << "Rectangle: Point(" << p1.Get_X() << "," << p1.Get_Y() << ") Width:" << width<< " Height:" << height << " Color:" << color << "\n";
	std::cout << std::endl;
}

void Rectangle::translate(double x, double y)
{
	p1.Translate(x, y);
}

bool Rectangle::within(const Rectangle& rhs) const
{
	if ((p1.Get_X() + width) < (rhs.p1.Get_X() + rhs.width) &&
		(p1.Get_Y() + height) < (rhs.p1.Get_Y() + rhs.height) &&
		(p1.Get_X() >= rhs.p1.Get_X()) &&
		(p1.Get_Y() >= rhs.p1.Get_Y()))
	{
		return true;
	}
	
	return false;
}

//a rectangle is saved in this format
//<rect x="..." y="..." width="..." height="..." fill="..." />
void Rectangle::saveInFile(std::fstream& file) const
{
	file << "<rect x=\"" << p1.Get_X() << "\" y=\"" << p1.Get_Y() 
		 << "\" width=\"" << width << "\" height=\"" << height 
		 << "\" fill=\"" << color << "\" />" << std::endl;
}

const char * Rectangle::getFigType() const
{
	return "rectangle";
}

Point Rectangle::getPoint() const
{
	return p1;
}

double Rectangle::getWidth() const
{
	return width;
}

double Rectangle::getHeight() const
{
	return height;
}
