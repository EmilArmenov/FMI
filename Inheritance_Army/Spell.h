#include <iostream>

#ifndef SPELL_H
#define SPELL_H

class Spell
{
public:
	Spell(std::string info = "", std::string type = "", unsigned power = 0);
	std::string getSpellInfo()const;
	int getSpellPower()const;

private:
	std::string spellInfo;
	std::string spellType;
	int spellPower;
};

#endif