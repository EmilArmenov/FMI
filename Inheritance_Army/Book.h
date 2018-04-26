#include "Spell.h"

#ifndef BOOK_H
#define BOOK_H

class SpellBook
{
public:
	SpellBook();
	SpellBook(const SpellBook& rhs);
	SpellBook& operator=(const SpellBook& rhs);
	~SpellBook();

public:
	void addSpell(const Spell& s);
	int usePage(int index, int& magePower);

private:
	void addPage();
	void swap(Spell& s1, Spell& s2);

private:
	int spellCounter;
	int pageCapacity;
	Spell* spell;
};

#endif