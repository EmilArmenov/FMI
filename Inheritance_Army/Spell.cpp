#include "Spell.h"

Spell::Spell(std::string info, std::string type, unsigned power):spellInfo(info), spellType(type), spellPower(power)
{}

std::string Spell::getSpellInfo() const
{
	return spellInfo;
}

int Spell::getSpellPower() const
{
	return spellPower;
}