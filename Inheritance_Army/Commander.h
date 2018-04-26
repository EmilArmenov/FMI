#include "Mage.h"
#include "Book.h"

#ifndef COMMANDER_H
#define COMMANDER_H

class Commander :public Soldier
{
public:
	Commander(std::string name = "", unsigned age = 45, unsigned skills = 0, unsigned gold = 0, unsigned mageCap = 1);
	Commander(const Commander& rhs);
	Commander & operator=(const Commander& rhs);
	~Commander();

public:
	int getCommandedAmount()const;
	void commandMage(const Mage& mg);
	void calculate()const;

private:
	unsigned capacity;
	int mageCounter;
	Mage* magesCommanded;
};

#endif
