#include "Boss.h"
int Boss::s_encounter = 0;

std::string Boss::boss[Boss::MAX_TYPES]
{
	{ "Minotaur" },
	{ "Elder Dragon" },
	{ "Giant Toad" },
	{ "Lich King" }
};

Boss Boss::getBoss()
{
	int level = (s_encounter + 1) * 25;
	int health = (s_encounter + 1) * 100;
	int attack = (s_encounter + 1) * 20;
	int defense = (s_encounter + 1) * 20;

	return Boss(boss[s_encounter], level, health, attack, defense);
}

Boss::Boss(std::string type,int level, int health, int attack, int defense)
	:Enemy{type,level, health,attack,defense}
{

}

void Boss::getStats(int x, int y)
{
	gotoxy(x, y);
	std::cout << "BOSS: ";
	gotoxy(x, ++y);
	std::cout << getName();
	gotoxy(x, ++y);
	std::cout << "Level: " << getLevel();
	gotoxy(x, ++y);
	std::cout << "Health: " << getHealth() << "/" << getMaxHealth();
	gotoxy(x, ++y);
	std::cout << "Attack: " << getAttack();
	gotoxy(x, ++y);
	std::cout << "Defense: " << getDefense();
}