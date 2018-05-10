#include "Figure.h"

Figure::Figure(const char * clr)
{
	init(clr);
}

Figure::Figure(const Figure & rhs)
{
	init(rhs.color);
}

Figure & Figure::operator=(const Figure & rhs)
{
	if (this!=&rhs)
	{
		delete[]color;
		init(rhs.color);
	}

	return *this;
}

Figure::~Figure()
{
	delete[]color;
}

void Figure::init(const char * clr)
{
	color = new char[strlen(clr) + 1];
	strcpy((char*)color, clr);
}
