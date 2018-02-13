#include "Potion.h"

inline int generateRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

Potion::Potion(Potion::Type type)
	:m_name{ Potion::name[type] }
{
	m_empty = false;
}

Potion::Potion()
{

}

std::string Potion::name[Potion::MAX_TYPE]
{
	{"HEALING"},
	{"ANTIDOTE"},
	{"COOLING"},
	{"BLOOD"}
};

Potion Potion::getRandomPotion()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();
	int num = generateRandomNumber(0, MAX_TYPE - 1);
	return Potion(static_cast<Type>(num));
}

std::string Potion::getName()
{
	return m_name;
}

void Potion::setName(std::string name)
{
	m_name = name;
}

void Potion::setUsed(bool state)
{
	m_used = state;
}

bool Potion::getIfUsed()
{
	return m_used;
}

void Potion::setEmpty(bool state)
{
	m_empty = state;
}

bool Potion::getIfEmpty()
{
	return m_empty;
}
