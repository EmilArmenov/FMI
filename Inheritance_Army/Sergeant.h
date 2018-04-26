#include "Soldier.h"

#ifndef SERGEANT_H
#define SERGEANT_H

class Sergeant : public Soldier
{
public:
	Sergeant(std::string name = "", unsigned age = 30, unsigned skills = 0, unsigned gold = 0, unsigned soldierCap = 1);
	Sergeant(const Sergeant& rhs);
	Sergeant & operator=(const Sergeant& rhs);
	~Sergeant();

public:
	void commandSoldier(const Soldier& s);
	int getSoldierGold()const;
	int getSoldierSkills()const;
	int getArmyAmount()const;

private:
	int soldierCounter;
	unsigned capacity;
	Soldier* soldiersCommanded;
};

#endif