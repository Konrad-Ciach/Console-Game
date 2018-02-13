#include "Trap.h"

inline int generateRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

std::string Trap::trap[Trap::MAX_TYPE]
{
	{"Fire"},
	{"Poisonous"},
	{"Lacerating"}
};

Trap::Trap(int x)
	:m_type{Trap::trap[x]}
{

}

Trap Trap::getRandomTrap()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();
	int num = generateRandomNumber(0, Trap::MAX_TYPE - 1);
	return Trap(num);

}

std::string Trap::getType()
{
	return m_type;
}