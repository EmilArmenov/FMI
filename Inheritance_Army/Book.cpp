#include "Book.h"

SpellBook::SpellBook(): spellCounter(0), pageCapacity(1)
{
	spell = new Spell[pageCapacity];
}

SpellBook::~SpellBook()
{
	delete[]spell;
}

SpellBook::SpellBook(const SpellBook & rhs)
{
	spellCounter = rhs.spellCounter;
	pageCapacity = rhs.pageCapacity;

	try
	{
		spell = new Spell[pageCapacity];
	}
	catch (const std::exception& ba)
	{
		std::cout << ba.what();
	}

	for (int i = 0; i < spellCounter; i++)
		spell[i] = rhs.spell[i];
}

SpellBook & SpellBook::operator=(const SpellBook & rhs)
{
	if (this != &rhs)
	{
		delete[]spell;

		spellCounter = rhs.spellCounter;
		pageCapacity = rhs.pageCapacity;

		try
		{
			spell = new Spell[pageCapacity];
		}
		catch (const std::exception& ba)
		{
			std::cout << ba.what();
		}

		for (int i = 0; i < spellCounter; i++)
			spell[i] = rhs.spell[i];
	}
	return *this;
}

void SpellBook::addSpell(const Spell & s)
{
	if (spellCounter == pageCapacity - 1)
		addPage();
	
	spell[spellCounter] = s;
	spellCounter++;
}

void SpellBook::addPage()
{
	Spell* temp = new Spell[pageCapacity+1];
	for (int i = 0; i < spellCounter; i++)
		temp[i] = spell[i];

	delete[]spell;
	spell = temp;
	pageCapacity += 1;
}

void SpellBook::swap(Spell & s1, Spell & s2)
{
	Spell temp = s1;
	s1 = s2;
	s2 = temp;
}

int SpellBook::usePage(int index, int& magePower)
{
	if (index > spellCounter || index < 0)
		throw std::out_of_range("This page doesn't exist in the book \n");

	int spellDamage = spell[index].getSpellPower();

	if (magePower<spellDamage)
	{
		std::cout << "Not enough mana for this spell \n";
		return 0;
	}

	magePower -= spellDamage;
	for (int j = index; j < spellCounter - 1; j++)
		swap(spell[j], spell[j + 1]);

	spellCounter--;
	return spellDamage;
}
