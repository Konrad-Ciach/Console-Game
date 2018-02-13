#include "Enemy.h"
#include"PlayerCharacter.h"
#include<ctime>

inline int generateRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

std::string Enemy::monsterType[Enemy::MAX_TYPES]
{

	{ "Dragon"},// +attack 
	{ "Orc"},// + hp +att +def
	{ "Slime"},// player - 1def
	{ "Rat",},//player shocked for 5 turns
	{ "Yeti"},// + hp
	{ "Skeleton"},// + def
	{ "Goblin"}// has first strike
};

 Enemy Enemy::getRandomMonster()
{
	 srand(static_cast<unsigned int>(time(0)));
	 rand();
	int num = generateRandomNumber(0, MAX_TYPES - 1);
	double level = generateRandomNumber(PlayerCharacter::s_level, PlayerCharacter::s_level + 1);
	double health = generateRandomNumber(PlayerCharacter::s_level * 2 + 2, PlayerCharacter::s_level * 2 + 5);
	double attack = generateRandomNumber(PlayerCharacter::s_level + 1, PlayerCharacter::s_level + 2);
	double defense = generateRandomNumber(PlayerCharacter::s_level - 1, PlayerCharacter::s_level);

	return Enemy(monsterType[num] , level , health , attack , defense);
}

Enemy::Enemy(std::string type, int level, double health, double attack, double defense)
	:Character{ type, health, attack , defense } , m_level{ level }
{

}

int Enemy::getLevel()
{
	return m_level;
}

void Enemy::getStats(int x, int y)
{
	gotoxy(x, y);
	std::cout << "Enenmy: ";
	gotoxy(x, ++y);
	std::cout << "Enemy type: " << getName();
	gotoxy(x, ++y);
	std::cout << "Level: " << getLevel();
	gotoxy(x, ++y);
	std::cout << "Health: " << getHealth() << "/" << getMaxHealth();
	gotoxy(x, ++y);
	std::cout << "Attack: " << getAttack();
	gotoxy(x, ++y);
	std::cout << "Defense: " << getDefense();
	
}


