#pragma once
#include"PlayerCharacter.h"
#include"Enemy.h"
#include"MapGeneration.h"
#include"Item.h"
#include"Trap.h"
#include"Boss.h"
#include<fstream>
#include<vector>

#define SHOW_MAP false
#define TEST_MODE false
#define No_Skills 3

class Interface
{
private:
	static int s_turnCount;
public:
	
	enum class Case
	{
		FIGHT,
		ITEM,
		TRAP,
		NEXT_LEVEL,
		WON,
		RUN,
		DEAD,
		MENU,
		POTION,
		BOSS,
		SAVE,
		MAX_CASE

	};

	enum class Fight
	{
		ATTACK,
		SKILLS,
		ITEM,
		RUN,
		MAX_CASE
	};

	enum class Items
	{
		USE,
		DISCARD,
		CANCEL,
		MAX_CASE
	};

	enum class Menu
	{
		CONTINUE,
		ITEMS,
		STATS,
		RESTART_LEVEL,
		QUIT,
		MAX_CASE
	};

	enum class Skills
	{
		QUICK_ATTACK,
		NORMAL_ATTACK,
		STRONG_ATTACK,
		MAX_CASE
	};

	enum class SkillsChoice
	{
		USE,
		CANCEL,
		MAX_CASE
	};

	enum class MainMenu
	{
		NEW_GAME,
		LOAD_GAME,
		QUIT_GAME,
		MAX_CASE
	};

	static std::string Skills[No_Skills];
	
	Case fight(PlayerCharacter &player, Enemy &enemy);
	Case movement(MapGeneration &map ,PlayerCharacter &player, int &location);
	void moveMonster(int x, int y, MapGeneration &map);
	void moveCharacter(MapGeneration &map, int startX, int startY, int endX, int endY,char ch='@');
	void printInfo();
	void clearLocation(MapGeneration &map, int location);
	void nextLevel(MapGeneration &map);
	void gotItem(PlayerCharacter &player, Item &item);
	void gotTrapped(PlayerCharacter &player, Trap &trap);
	void gotPotion(PlayerCharacter &player, Potion &potion);
	Menu menu();
	void showPotions(PlayerCharacter &player,Enemy &enemy, int x, int y);
	bool showPotions(PlayerCharacter &player,int x, int y);
	void usePotion(PlayerCharacter &player, int x);
	void checkStatus(Character &character);
	void showSkills(PlayerCharacter &player,Enemy &enemy, int x, int y);
	void useSkill(Enemy &enemy, int skill);
	void mainMenu();
	void newGame();
	void loadGame();
	void save(PlayerCharacter &player);
	void Game(PlayerCharacter &player, MapGeneration &map);
};