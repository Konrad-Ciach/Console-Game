#include "Item.h"
#include<ctime>
#include<iostream>

inline int generateRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

Item::Item(Item::Type type)
	:m_name{ items[type].name }, m_health{ items[type].health }, m_attack{ items[type].attack }, m_defense{ items[type].defense }
{

}

Item::Parameters Item::items[Item::MAX_TYPE]
{
	{"Ring",1},
	{"Amulet",1},
	{"Talisman",1},
	{"Belt",1},
	{"Sword",0,1},
	{"Axe",0,1},
	{"Mace",0,1},
	{"Dagger",0,1},
	{"Armor",0,0,1},
	{"Gauntlets",0,0,1},
	{"Pants",0,0,1},
	{"Helmet",0,0,1}
};

Item Item::getRandomItem()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();
	int num = generateRandomNumber(0, Item::MAX_TYPE - 1);
	return Item(static_cast<Type>(num));
}
