#pragma once
#include <iostream>

class Point 
{
public:
	Point(double X = 0.0, double Y = 0.0);

	double Get_X()const;
	double Get_Y()const;

	void Print()const;
	Point& Translate(double x, double y);

private:
	double x;
	double y;
};
