#include "Mage.h"

Mage::Mage():Soldier("", 50, 0, 0), capacity(1), mageMana(0), sergeantCounter(0)
{
	sergeantsCommanded = new Sergeant[capacity];
}

Mage::Mage(std::string name, unsigned age, unsigned skills, unsigned gold, unsigned sergCap, int mana, const SpellBook& sBook)
	: Soldier(name, age, skills, gold), capacity(sergCap), mageMana(mana), sergeantCounter(0), book(sBook)
{
	sergeantsCommanded = new Sergeant[capacity];
}

Mage::~Mage()
{
	delete[]sergeantsCommanded;
}

Mage::Mage(const Mage & rhs) : Soldier(rhs)
{
	capacity = rhs.capacity;
	sergeantCounter = rhs.sergeantCounter;
	sergeantsCommanded = new Sergeant[capacity];

	for (int i = 0; i < sergeantCounter; i++)
		sergeantsCommanded[i] = rhs.sergeantsCommanded[i];

	book = rhs.book;
	mageMana = rhs.mageMana;
}

Mage & Mage::operator=(const Mage & rhs)
{
	if (this != &rhs)
	{
		Soldier::operator=(rhs);

		delete[]sergeantsCommanded;

		capacity = rhs.capacity;
		sergeantCounter = rhs.sergeantCounter;
		sergeantsCommanded = new Sergeant[capacity];

		for (int i = 0; i < sergeantCounter; i++)
			sergeantsCommanded[i] = rhs.sergeantsCommanded[i];

		book = rhs.book;
		mageMana = rhs.mageMana;
	}
	return *this;
}

void Mage::commandSergeant(const Sergeant & sergeant)
{
	if (sergeantCounter == capacity)
	{
		std::cout << "The mage can't command more than " << capacity << " sergeants \n";
		return;
	}

	if (sergeant.getSkills()>skills)
	{
		std::cout << "The skills of this soldier are too big for tis sergeant \n";
		return;
	}

	sergeantsCommanded[sergeantCounter] = sergeant;
	sergeantCounter++;
}

void Mage::learnSpell(const Spell& s)
{
	book.addSpell(s);
}

int Mage::useSpell(int page)
{
	return book.usePage(page, mageMana);
}

int Mage::getBattalionGold()const
{
	int sum = 0;
	for (int i = 0; i < sergeantCounter; i++)
	{
		sum += sergeantsCommanded[i].getGold();
		sum += sergeantsCommanded[i].getSoldierGold();
	}
	return sum;
}

int Mage::getBattalionSkills()const
{
	int sum = 0;
	for (int i = 0; i < sergeantCounter; i++)
	{
		sum += sergeantsCommanded[i].getSkills();
		sum += sergeantsCommanded[i].getSoldierSkills();
	}
	return sum;
}

int Mage::getMana() const
{
	return mageMana;
}

int Mage::getArmyAmount() const
{
	int armyAmount = 0;
	for (int i = 0; i < sergeantCounter; i++)
		armyAmount += sergeantsCommanded[i].getArmyAmount();
	
	armyAmount += sergeantCounter;
	return armyAmount;
}
