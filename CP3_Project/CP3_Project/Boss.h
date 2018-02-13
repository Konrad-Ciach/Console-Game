#pragma once
#include "Enemy.h"
class Boss :public Enemy
{

public:
	static int s_encounter;
	Boss(std::string type, int level, int health, int attack, int defense);
	enum Type
	{
		ELDER_DRAGON,
		GIANT_TOAD,
		LICH_KING,
		RNGESUS,
		MAX_TYPES
	};

	static std::string boss[MAX_TYPES];
	static Boss getBoss();
	virtual void getStats(int x = 70, int y = 2);
};

