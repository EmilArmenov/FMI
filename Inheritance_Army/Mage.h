#include "Sergeant.h"
#include"Book.h"

#ifndef MAGE_H
#define MAGE_H

class Mage : public Soldier
{
public:
	Mage();
	Mage(std::string name, unsigned age, unsigned skills, unsigned gold, unsigned sergCap, int mana, const SpellBook& sBook);
	Mage(const Mage& rhs);
	Mage & operator=(const Mage& rhs);
	~Mage();

public:
	void commandSergeant(const Sergeant& sergeant);
	void learnSpell(const Spell& s);
	int useSpell(int page);
	int getBattalionGold()const;
	int getBattalionSkills()const;
	int getMana()const;
	int getArmyAmount()const;

private:
	unsigned capacity;
	int mageMana;
	int sergeantCounter;
	SpellBook book;
	Sergeant* sergeantsCommanded;
};

#endif
