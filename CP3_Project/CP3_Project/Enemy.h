#pragma once
#include"Character.h"


class Enemy:public Character
{
private:
	int m_level;

public:
	enum Type
	{
		DRAGON,
		ORC,
		SLIME,
		RAT,
		YETI,
		SKELETON,
		GOBLIN,
		MAX_TYPES
	};

	Enemy(std::string type , int level , double health , double attack , double defense);
	static std::string monsterType[MAX_TYPES];
	static Enemy getRandomMonster();
	int getLevel();
	virtual void getStats(int x = 70, int y = 2);
};

