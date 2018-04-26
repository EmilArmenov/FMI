#include <iostream>

#ifndef SOLDIER_H
#define SOLDIER_H

class Soldier
{
public:
	Soldier(std::string name = "", unsigned age = 20, unsigned skills = 0, unsigned gold = 0);
	std::string getName()const;
	unsigned getYears()const;
	unsigned getSkills()const;
	unsigned getGold()const;

protected:
	std::string name;
	unsigned age;
	unsigned skills;
	unsigned gold;
};

#endif 