#include "Basket.h"

Basket::Basket(const char * owner) : ownerName{ new char[strlen(owner) + 1] }, eggCounter(0), capacity(1), eggs{ new Egg[capacity] }
{
	strcpy((char*)ownerName, owner);
}

Basket::Basket(const Basket & rhs)
{
	ownerName = new char[strlen(rhs.ownerName) + 1];
	strcpy((char*)ownerName, rhs.ownerName);

	eggCounter = rhs.eggCounter;
	capacity = rhs.capacity;
	eggs = new Egg[capacity];

	for (int i = 0; i < eggCounter; i++)
		eggs[i] = rhs.eggs[i];
}

Basket & Basket::operator=(const Basket & rhs)
{
	if (this!=&rhs)
	{
		delete[] ownerName;
		delete[] eggs;

		ownerName = new char[strlen(rhs.ownerName) + 1];
		strcpy((char*)ownerName, rhs.ownerName);

		eggCounter = rhs.eggCounter;
		capacity = rhs.capacity;
		eggs = new Egg[capacity];

		for (int i = 0; i < eggCounter; i++)
			eggs[i] = rhs.eggs[i];
	}

	return *this;
}

Basket::~Basket()
{
	delete[] ownerName;
	delete[] eggs;
}

void Basket::addEgg(const Egg & egg)
{
	if (eggCounter==capacity)
	{
		capacity += capacity;
		resize(capacity);
	}

	eggs[eggCounter] = egg;
	eggCounter++;
}

void Basket::removeEgg(const char * eggName)
{
	int i;
	for (i = 0; i < eggCounter; i++)
	{
		if (strcmp(eggs[i].getName(), eggName) == 0)
		{
			for (int j = i; j < eggCounter - 1; j++)
				swap(eggs[j], eggs[j + 1]);

			break;
		}
	}

	if (i == eggCounter)
		std::cout << "The egg with name " << eggName << " doesn't exist in the basket \n";

	else
		eggCounter--;
}

std::ostream& operator<<(std::ostream& out, const Basket& b)
{
	for (int i = 0; i < b.getEggsAmount(); i++)
		out << b[i];

	return out;
}

const char * Basket::getOwner() const
{
	return ownerName;
}

int Basket::getEggsAmount() const
{
	return eggCounter;
}

void Basket::write(const char* path)
{
	std::ofstream out(path, std::ios::binary);

	int size = strlen(ownerName);
	out.write((char*)&size, sizeof(size));
	out.write(ownerName, size + 1);
	out.write((char*)&eggCounter, sizeof(eggCounter));
	out.write((char*)&capacity, sizeof(capacity));

	for (int i = 0; i < eggCounter; i++)
		eggs[i].write(out);

	out.close();
}

void Basket::read(const char * path)
{
	std::ifstream in(path, std::ios::binary);

	int size;
	in.read((char*)&size, sizeof(size));
	ownerName = new char[size + 1];
	in.read((char*)ownerName, size + 1);
	int eggsAmount;
	in.read((char*)&eggsAmount, sizeof(eggsAmount));
	in.read((char*)&capacity, sizeof(capacity));

	resize(capacity);

	for (int i = 0; i < eggsAmount; i++)
		eggs[i].read(in);
	
	eggCounter = eggsAmount;
	in.close();
}

const Egg & Basket::operator[](int index) const
{
	if (index > eggCounter || index < 0)
		throw std::out_of_range("The given index is not in the scope \n");

	else
		return eggs[index];
}

const Egg & Basket::operator[](const char * eggName) const
{
	for (int i = 0; i < eggCounter; i++)
	{
		if (strcmp(eggs[i].getName(), eggName) == 0)
			return eggs[i];
	}

	throw std::invalid_argument("The given egg doesn't exist in the basket \n");
}

const Basket Basket::operator+(const Basket & rhs) const
{
	Basket obj = *this;
	obj += rhs;
	
	return obj;
}

Basket & Basket::operator+=(const Basket & rhs)
{
	for (int i = 0; i < rhs.eggCounter; i++)
		addEgg(rhs[i]);

	return *this;
}

const Basket Basket::operator%(const Basket & rhs) const
{
	Basket obj = *this;
	obj %= rhs;

	return obj;
}

Basket & Basket::operator%=(const Basket & rhs)
{
	for (int j, i = 0; i < eggCounter; i++)
	{
		for (j = 0; j < rhs.eggCounter; j++)
		{
			if (eggs[i]==eggs[j])
				break;
		}

		if (j==rhs.eggCounter)
			removeEgg(eggs[i].getName());
	}

	return *this;
}

Basket & Basket::operator+=(const char * extension)
{
	for (int i = 0; i < eggCounter; i++)
		eggs[i] += extension;

	return *this;
}

Basket & Basket::operator*=(short size)
{
	for (int i = 0; i < eggCounter; i++)
		eggs[i] *= size;

	return *this;
}

bool Basket::operator==(const Basket & rhs) const
{
	for (int i = 0; i < eggCounter; i++)
	{
		if (eggs[i]!=rhs.eggs[i])
			return false;
	}

	return true;
}

bool Basket::operator!=(const Basket & rhs) const
{
	return !(*this == rhs);
}

bool Basket::operator<(const Basket & rhs) const
{
	for (int i = 0; i < eggCounter; i++)
	{
		if (eggs[i] < rhs.eggs[i])
			return true;
	}

	return false;
}

bool Basket::operator>=(const Basket & rhs) const
{
	return !(*this < rhs);
}

bool Basket::operator>(const Basket & rhs) const
{
	for (int i = 0; i < eggCounter; i++)
	{
		if (eggs[i] < rhs.eggs[i])
			return false;
	}

	return true;
}

bool Basket::operator<=(const Basket & rhs) const
{
	return !(*this > rhs);
}

const Basket operator+(const Basket& b, const char* extension)
{
	Basket obj = b;
	obj += extension;
	return obj;
}

const Basket operator*(const Basket& b, short size) 
{
	Basket obj = b;
	obj *= size;
	return obj;
}

void Basket::resize(int size)
{
	if (size<=0)
		throw std::invalid_argument("The size can't be less than one \n");
	
	Egg* temp = new Egg[size];
	for (int i = 0; i < eggCounter; i++)
		temp[i] = eggs[i];
	
	delete[] eggs;
	eggs = temp;
}

void Basket::swap(Egg & e1, Egg & e2)
{
	Egg temp = e1;
	e1 = e2;
	e2 = temp;
}
