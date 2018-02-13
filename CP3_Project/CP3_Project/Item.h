#pragma once
#include<string>

class Item
{
private:
	std::string m_name;
	int m_health;
	int m_attack;
	int m_defense;
public:
	
	enum Type
	{
		RING,
		AMULET,
		TALISMAN,
		BELT,
		SWORD,
		AXE,
		MACE,
		DAGGER,
		ARMOR,
		GAUNTLETS,
		PANTS,
		HELMET,
		MAX_TYPE
	};
	struct Parameters
	{
		std::string name;
		int health = 0;
		int attack = 0;
		int defense = 0;
	};

	Item(Type type);

	static Parameters items[MAX_TYPE];
	static Item getRandomItem();
	friend class Interface;

};