#pragma once
#include <iostream>
#include <fstream>

class Egg 
{
public:
	Egg(const char* name = "", short size = 0);
	Egg(const Egg& rhs);
	Egg& operator=(const Egg& rhs);
	~Egg();

public:
	void write(std::ofstream& out);
	Egg& read(std::ifstream& in);

	char* getName()const;
	short getSize()const;

public:
	//adding another string at the end of the egg name
	//@param extension - the string to be added at the end of the name
	Egg& operator+=(const char* extension);

	//multiplying the size of the egg with @newEggSize
	Egg& operator*=(short newEggSize);

	bool operator==(const Egg& rhs)const;
	bool operator!=(const Egg& rhs)const;
	bool operator<(const Egg& rhs)const;
	bool operator>=(const Egg& rhs)const;
	bool operator>(const Egg& rhs)const;
	bool operator<=(const Egg& rhs)const;

private:
	//initializing the parameters of the egg
	void init(const char* name, short size);

	void setEggName(const char* name);

private:
	char* eggName;
	short eggSize;
};

const Egg operator+(const Egg& e, const char* extension);
const Egg operator*(const Egg& e, short newEggSize);
