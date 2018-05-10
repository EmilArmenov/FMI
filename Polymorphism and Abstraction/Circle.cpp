#include "Circle.h"

Circle::Circle():center(0,0),radius(0.0),Figure("white")
{}

Circle::Circle(Point p_1, double rad, const char* color): Figure(color), center(p_1), radius(rad)
{}

Circle::Circle(const Circle & rhs): Figure(rhs), center(rhs.center), radius(rhs.radius)
{}

Circle & Circle::operator=(const Circle & rhs)
{
	if (this!=&rhs)
	{
		Figure::operator=(rhs);
		center = rhs.center;
		radius = rhs.radius;
	}

	return *this;
}

void Circle::print() const
{
	std::cout << "Circle: Center(" << center.Get_X() << "," << center.Get_Y() << ") Radius:" << radius << " Color:" << color << "\n";
	std::cout << std::endl;
}

void Circle::translate(double x, double y)
{
	center.Translate(x, y);
}

bool Circle::within(const Rectangle & rhs) const
{
	if (rhs.getPoint().Get_X() < center.Get_X() && rhs.getPoint().Get_Y() < center.Get_Y() &&
		rhs.getPoint().Get_X() + rhs.getWidth() > center.Get_X() + radius && 
		rhs.getPoint().Get_Y() + rhs.getWidth() > center.Get_Y() + radius)
	{
		return true;
	}

	return false;
}

//a circle is saved in this format
//<circle cx="5" cy="5" r="10" fill="blue" />
void Circle::saveInFile(std::fstream & file) const
{
	file << "<circle cx=\"" << center.Get_X() << "\" cy=\"" << center.Get_Y()
		 << "\" r=\"" << radius << "\" fill=\"" << color << "\" />" << std::endl;
}

const char * Circle::getFigType() const
{
	return "circle";
}
