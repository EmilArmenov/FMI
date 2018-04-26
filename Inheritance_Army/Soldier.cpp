#include "Soldier.h"

Soldier::Soldier(std::string _name, unsigned _age, unsigned _skills, unsigned _gold): name(_name), age(_age), skills(_skills), gold(_gold)
{}

std::string Soldier::getName() const
{
	return name;
}

unsigned Soldier::getYears() const
{
	return age;
}

unsigned Soldier::getSkills() const
{
	return skills;
}

unsigned Soldier::getGold() const
{
	return gold;
}
