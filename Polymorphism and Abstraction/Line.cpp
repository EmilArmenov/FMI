#include "Line.h"

Line::Line() :p1(0, 0), p2(0, 0), strokeWidth(0.0), Figure("black")
{}

Line::Line(Point p_1, Point p_2, double stroke, const char * color) : Figure(color), p1(p_1), p2(p_2), strokeWidth(stroke)
{}

Line::Line(const Line & rhs): Figure(rhs), p1(rhs.p1), p2(rhs.p2), strokeWidth(rhs.strokeWidth)
{}

Line & Line::operator=(const Line & rhs)
{
	if (this!=&rhs)
	{
		Figure::operator=(rhs);
		p1 = rhs.p1;
		p2 = rhs.p2;
		strokeWidth = rhs.strokeWidth;
	}

	return *this;
}


void Line::print() const
{
	std::cout << "Line: Point1(" << p1.Get_X() << "," << p1.Get_Y() << ") " << "Point2(" << p2.Get_X() << "," << p2.Get_Y() << ")"
			  << " Stroke:" << strokeWidth << " Color:" << color << "\n";

	std::cout << std::endl;
}

void Line::translate(double x, double y)
{
	p1.Translate(x, y);
	p2.Translate(x, y);
}

bool Line::within(const Rectangle& rhs) const
{
	if ((p1.Get_X() > rhs.getPoint().Get_X() && p1.Get_X() < rhs.getPoint().Get_X() + rhs.getWidth())
		&& (p1.Get_Y() > rhs.getPoint().Get_Y() && p1.Get_Y() < rhs.getPoint().Get_Y() + rhs.getHeight())
		&& (p2.Get_X() < rhs.getPoint().Get_X() + rhs.getWidth() && p2.Get_X() > rhs.getPoint().Get_X())
		&& (p2.Get_Y() < rhs.getPoint().Get_Y() + rhs.getHeight() && p2.Get_X() > rhs.getPoint().Get_X()))
	{
		return true;
	}

	return false;
}

//a line is saved in this format
//<line x1="100" y1="300" x2="300" y2="100" stroke-width="5" stroke="green" />
void Line::saveInFile(std::fstream & file) const
{
	file << "<line x1=\"" << p1.Get_X() << "\" y1=\"" << p1.Get_Y() <<"\" x2=\"" <<p2.Get_X() <<"\ y2=\""<<p2.Get_Y()
		 << "\" stroke-width=\"" << strokeWidth << "\" stroke=\"" << color << "\" />" << std::endl;
}

const char * Line::getFigType() const
{
	return "line";
}
