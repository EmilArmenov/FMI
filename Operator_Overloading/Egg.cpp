#include "Egg.h"

Egg::Egg(const char * name, short size)
{
	init(name, size);
}

Egg::Egg(const Egg & rhs)
{
	init(rhs.eggName, rhs.eggSize);
}

Egg & Egg::operator=(const Egg & rhs)
{
	if (this!=&rhs)
	{
		delete[] eggName;
		init(rhs.eggName, rhs.eggSize);
	}

	return *this;
}

Egg::~Egg()
{
	delete[] eggName;
}

void Egg::write(std::ofstream & out)
{
	int size = strlen(eggName);
	out.write((char*)&size, sizeof(size));
	out.write(eggName, size + 1);
	out.write((char*)&eggSize, sizeof(eggSize));
}

Egg& Egg::read(std::ifstream & in)
{
	int size;
	in.read((char*)&size, sizeof(size));
	eggName = new char[size + 1];
	in.read(eggName, size + 1);
	in.read((char*)&eggSize, sizeof(eggSize));
	return *this;
}

char * Egg::getName() const
{
	return eggName;
}

short Egg::getSize() const
{
	return eggSize;
}

Egg & Egg::operator+=(const char * extension)
{
	char* newName = new char[strlen(eggName) + strlen(extension) + 1];
	strcpy(newName, eggName);
	strcat(newName, extension);
	setEggName(newName);
	delete[] newName;
	return *this;
}

Egg & Egg::operator*=(short newEggSize)
{
	eggSize *= newEggSize;
	return *this;
}

bool Egg::operator==(const Egg & rhs) const
{
	return (strcmp(eggName, rhs.eggName) == 0) ? true : false;
}

bool Egg::operator!=(const Egg & rhs) const
{
	return !(*this == rhs);
}

bool Egg::operator<(const Egg & rhs) const
{
	return (strcmp(eggName, rhs.eggName) < 0) ? true : false;
}

bool Egg::operator>=(const Egg & rhs) const
{
	return !(*this < rhs);
}

bool Egg::operator>(const Egg & rhs) const
{
	return (strcmp(eggName, rhs.eggName) > 0) ? true : false;
}

bool Egg::operator<=(const Egg & rhs) const
{
	return !(*this > rhs);
}

const Egg operator+(const Egg& e, const char* extension) 
{
	Egg obj = e;
	obj += extension;
	return obj;
}

const Egg operator*(const Egg& e, short newEggSize) 
{
	Egg obj = e;
	obj *= newEggSize;
	return obj;
}

void Egg::init(const char * name, short size)
{
	setEggName(name);

	if (size < 0)
		throw std::invalid_argument("The size can't be a negative number \n");

	eggSize = size;
}

void Egg::setEggName(const char * name)
{
	try
	{
		eggName = new char[strlen(name) + 1];
	}
	catch (const std::exception& ba)
	{
		std::cout << ba.what();
	}
	strcpy(eggName, name);
}
