#include "Point.h"

Point::Point(double X, double Y): x(X), y(Y)
{}

double Point::Get_X() const
{
	return x;
}

double Point::Get_Y() const
{
	return y;
}

void Point::Print() const
{
	std::cout << "X:" << x << " ";
	std::cout << "Y:" << y << " ";
	std::cout << std::endl;
}

Point & Point::Translate(double x, double y)
{
	this->x += x;
	this->y += y;

	return *this;
}
