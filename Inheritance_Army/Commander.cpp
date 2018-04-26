#include "Commander.h"

Commander::Commander(std::string name, unsigned age, unsigned skills, unsigned gold, unsigned mageCap): 
	Soldier(name, age, skills, gold), capacity(mageCap), mageCounter(0)
{
	magesCommanded = new Mage[capacity];
}

Commander::~Commander()
{
	delete[]magesCommanded;
}

Commander::Commander(const Commander & rhs) :Soldier(rhs)
{
	capacity = rhs.capacity;
	mageCounter = rhs.mageCounter;
	magesCommanded = new Mage[capacity];

	for (int i = 0; i < mageCounter; i++)
		magesCommanded[i] = rhs.magesCommanded[i];
}

Commander & Commander::operator=(const Commander & rhs)
{
	if (this != &rhs)
	{
		Soldier::operator=(rhs);
		delete[]magesCommanded;

		capacity = rhs.capacity;
		mageCounter = rhs.mageCounter;
		magesCommanded = new Mage[capacity];

		for (int i = 0; i < mageCounter; i++)
			magesCommanded[i] = rhs.magesCommanded[i];
	}
	return *this;
}

int Commander::getCommandedAmount() const
{
	return mageCounter;
}

void Commander::commandMage(const Mage & mg)
{
	magesCommanded[mageCounter] = mg;
	mageCounter++;
}

void Commander::calculate()const
{
	int magesMana = 0;
	int armySalary = 0;
	int armySkills = 0;
	int armyAmount = 0;

	for (int i = 0; i < mageCounter; i++)
	{
		magesMana  += magesCommanded[i].getMana();
		armySalary += magesCommanded[i].getBattalionGold() + magesCommanded[i].getGold() + getGold();
		armySkills += magesCommanded[i].getBattalionSkills() + magesCommanded[i].getSkills() + getSkills();
		armyAmount += magesCommanded[i].getArmyAmount();
	}

	armyAmount += mageCounter;
	std::cout << "Overall mage power is: " << magesMana << std::endl;
	std::cout << "Average mage power is: " << (double)magesMana / mageCounter << std::endl;

	std::cout << "Overall army skills are: " << armySkills << std::endl;
	std::cout << "Average army skills are: " << (double) armySkills / armyAmount << std::endl;

	std::cout << "The commander will need " << armySalary << " gold to support the army" << std::endl;
}