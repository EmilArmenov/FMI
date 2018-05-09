#pragma once
#include "Egg.h"

class Basket 
{
	//operator used to save eggs of a basket in a text file
	friend std::ostream& operator<<(std::ostream& out, const Basket& b);

public:
	Basket(const char* owner = "unknown");
	Basket(const Basket& rhs);
	Basket& operator=(const Basket& rhs);
	~Basket();

public:
	//adds an egg at the end of the eggs array
	void addEgg(const Egg& egg);

	//removes the first egg with the name @eggName
	void removeEgg(const char* eggName);

	const char* getOwner()const;

	//returns the egg counter
	int getEggsAmount()const;

	//writing the info of a basket in e binary file
	//@path - the path where the file should be added
	void write(const char* path);

	//reading the info for a basket from a binary file
	//@path - the path where the file should be added
	void read(const char* path);

public:
	//returns the egg at the given index
	const Egg& operator[](int index)const;

	//returns the first egg with the same name as @eggName
	const Egg& operator[] (const char* eggName)const;

	//adds all the eggs from @rhs in the basket
	const Basket operator+(const Basket& rhs)const;
	Basket& operator+=(const Basket& rhs);

	//leaves only the eggs that exist in the @rhs 
	//an egg exists in the basket if its name can be found in @rhs 
	const Basket operator%(const Basket& rhs)const;
	Basket& operator%=(const Basket& rhs);

	//adds @extension to every egg name in the basket
	Basket& operator+=(const char* extension);

	//multiplying the size of every egg in the basket
	//@param size - to be multiplied with every egg size in the basket
	Basket& operator*=(short size);

	bool operator==(const Basket& rhs) const;
	bool operator!=(const Basket& rhs) const;
	bool operator<(const Basket& rhs)const;
	bool operator>=(const Basket& rhs)const;
	bool operator>(const Basket& rhs)const;
	bool operator<=(const Basket& rhs)const;

private:
	//allocates new memory for the eggs array
	//@param size - the size of the new array
	void resize(int size);

	void swap(Egg& e1, Egg& e2);

private:
	const char* ownerName;
	int eggCounter;
	unsigned capacity;
	Egg* eggs;
};

const Basket operator+(const Basket& b, const char* extension);
const Basket operator*(const Basket& b, short size);
