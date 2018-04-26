#include "Sergeant.h"

Sergeant::Sergeant(std::string name, unsigned age, unsigned skills, unsigned gold, unsigned cap) :Soldier(name, age, skills, gold), 
																								  soldierCounter(0), capacity(cap), soldiersCommanded{new Soldier[capacity]}
{}

Sergeant::~Sergeant()
{
	delete[]soldiersCommanded;
}

Sergeant::Sergeant(const Sergeant & rhs) : Soldier(rhs)
{
	soldierCounter = rhs.soldierCounter;
	capacity = rhs.capacity;
	soldiersCommanded = new Soldier[capacity];

	for (int i = 0; i < soldierCounter; i++)
		soldiersCommanded[i] = rhs.soldiersCommanded[i];
}

Sergeant & Sergeant::operator=(const Sergeant & rhs)
{
	if (this!=&rhs)
	{
		Soldier::operator=(rhs);

		delete[]soldiersCommanded;
		soldierCounter = rhs.soldierCounter;
		capacity = rhs.capacity;
		soldiersCommanded = new Soldier[capacity];

		for (int i = 0; i < soldierCounter; i++)
			soldiersCommanded[i] = rhs.soldiersCommanded[i];
	}
	return *this;
}

void Sergeant::commandSoldier(const Soldier & s)
{
	if (soldierCounter==capacity)
	{
		std::cout << "The sergeant can't command more than " << capacity << " soldiers \n";
		return;
	}

	if (s.getSkills()>skills)
	{
		std::cout << "The skills of this soldier are too big for tis sergeant \n";
		return;
	}

	soldiersCommanded[soldierCounter] = s;
	soldierCounter++;
}

int Sergeant::getSoldierGold()const 
{
	int sum = 0;

	for (int i = 0; i < soldierCounter; i++)
		sum += soldiersCommanded[i].getGold();
	
	return sum;
}

int Sergeant::getSoldierSkills()const
{
	int sum = 0;

	for (int i = 0; i < soldierCounter; i++)
		sum += soldiersCommanded[i].getSkills();
	
	return sum;
}

int Sergeant::getArmyAmount() const
{
	return soldierCounter;
}

