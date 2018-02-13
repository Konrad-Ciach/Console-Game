#pragma once
#include"Character.h"
#include"Potion.h"


class PlayerCharacter:public Character
{
private:
	static int s_level;
	static int s_exp;
	static int s_multiplier;
	Potion **ptr = new Potion*[10];
	
public:
	PlayerCharacter(std::string name);
	~PlayerCharacter()
	{
		delete[] ptr;
	}
	void setLevel(int level);
	void changeLevel(int level, char sign = '+');
	int getLevel();
	void setExperience(int exp);
	int getExperience();
	virtual void getStats(int x = 5, int y = 2);
	void gainExperience(int exp);
	bool levelUp();
	void setPotions();
	void addPotion(Potion &potion);
	void removePotion(int x);
	void TestMode();
	friend class Enemy;
	friend class Interface;
};