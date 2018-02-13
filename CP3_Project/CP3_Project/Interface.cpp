#include "Interface.h"
#define NUMBER_OF_MONSTERS 25

int Interface::s_turnCount = 1;

inline int generateRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

std::string Interface::Skills[No_Skills]
{
	{"Quick Attack"},
	{"Normal Attack"},
	{"Strong Attack"}
};

Interface::Case Interface::fight(PlayerCharacter &player, Enemy &enemy)
{
	bool playerTurn = true;
	if (enemy.getName() == "Dragon")
	{
		enemy.setMaxAttack((PlayerCharacter::s_level * 2) - 1);
		enemy.setAttack(enemy.getMaxAttack());
	}
	else if (enemy.getName() == "Orc")
	{
		enemy.setMaxAttack(PlayerCharacter::s_level);
		enemy.setAttack(enemy.getMaxAttack());
		enemy.setMaxDefense(PlayerCharacter::s_level);
		enemy.setDefense(enemy.getMaxDefense());
		enemy.setMaxHealth(PlayerCharacter::s_level * 2);
		enemy.setHealth(enemy.getMaxHealth());
	}
	else if (enemy.getName() == "Slime")
	{
		player.changeDefense(1, '-');
	}
	else if (enemy.getName() == "Rat")
	{
		player.setShocked(5);
	}
	else if (enemy.getName() == "Yet")
	{
		enemy.setMaxHealth(PlayerCharacter::s_level * 3);
		enemy.setHealth(enemy.getMaxHealth());

	}
	else if (enemy.getName() == "Skeleton")
	{
		enemy.setMaxDefense((PlayerCharacter::s_level * 2) - 1);
		enemy.setDefense(enemy.getMaxDefense());
	}
	while (true)
	{
		rlutil::cls();
		
		enemy.getStats();
		player.getStats();
		gotoxy(35, 2);
		std::cout << "Turn: " << s_turnCount;
		int iniY{ 10 }, tempY{iniY};
		gotoxy(3, tempY);
		std::cout << "Attack";
		gotoxy(3, ++tempY);
		std::cout << "Skills";
		gotoxy(3, ++tempY);
		std::cout << "Items";
		gotoxy(3, ++tempY);
		std::cout << "Run";
		int choice{ 0 }, finY{ tempY };
		rlutil::CursorHider curs;
		int x{ 10 }, y{ 10 };
		gotoxy(x, y); std::cout << "*";
		if (s_turnCount == 1)
		{
			if (enemy.getName() == "Goblin")
			{
				playerTurn = false;
				gotoxy(1, 13);
				std::cout << "The enemy got first strike \n";
			}
			else
			{
				int firstStrikeChance = generateRandomNumber(1, 10);
				if (firstStrikeChance >= 7)
				{
					playerTurn = false;
					gotoxy(1, 13);
					std::cout << "The enemy got first strike \n";
				}
			}
			
		}

		checkStatus(player);
		checkStatus(enemy);
		if (enemy.isDead())
		{
			gotoxy(3, ++tempY);
			player.gainExperience(enemy.getLevel() * 2);
			std::cout << "You have killed the " << enemy.getName() << " and have gained " << enemy.getLevel() * 2 << " experience\n";
			if (player.levelUp())
				std::cout << "Congratulations! You have leveled up!";
			rlutil::anykey();
			MapGeneration::s_monsterCount--;
			s_turnCount = 1;
			return Case::WON;
		}
		if (playerTurn)
		{
			
			while (true)
			{
				if (kbhit())
				{
					gotoxy(x, y); std::cout << " ";
					int k = rlutil::getkey();
					if (k == rlutil::KEY_UP || k == 'w')
					{
						if (y == iniY)
						{
							y = finY;
							choice = static_cast<int>(Fight::MAX_CASE) - 1;
						}
						else
						{
							y--;
							choice--;
						}
					}
					else if (k == rlutil::KEY_DOWN || k == 's')
					{
						if (y == finY)
						{
							y = iniY;
							choice = static_cast<int>(Fight::ATTACK);
						}
						else
						{
							y++;
							choice++;
						}
					}
					else if (k == rlutil::KEY_ENTER || k == 'e') break;
					gotoxy(x, y); std::cout << "*";
				}
			}
			
			switch (static_cast<Fight>(choice))
			{
			case Fight::ATTACK:				
				gotoxy(1, 14);
				if (player.isShocked())
				{
					int chanceToMiss = generateRandomNumber(1, 10);
					if (chanceToMiss <= 5)
					{
						std::cout << "You have missed your attack since you are shocked";
						playerTurn = false;
					}
					else
					{
						enemy.changeHealth(player.getAttack() - enemy.getDefense());
						std::cout << "You have dealt " << ((player.getAttack() - enemy.getDefense()) > 0 ? player.getAttack() - enemy.getDefense() : 1) << " damage to the " << enemy.getName() << '\n';
						playerTurn = false;
					}
				}
				else
				{
					enemy.changeHealth(player.getAttack() - enemy.getDefense());
					std::cout << "You have dealt " << ((player.getAttack() - enemy.getDefense()) > 0 ? player.getAttack() - enemy.getDefense() : 1) << " damage to the " << enemy.getName() << '\n';
					playerTurn = false;
				}
				if (enemy.isDead())
				{
					player.gainExperience(enemy.getLevel() * 2);
					std::cout << "You have killed the " << enemy.getName() << " and have gained " << enemy.getLevel() * 2 << " experience\n";
					if (player.levelUp())
						std::cout << "Congratulations! You have leveled up!";
					rlutil::anykey();
					MapGeneration::s_monsterCount--;
					s_turnCount = 1;
					return Case::WON;
				}
				s_turnCount++;
				rlutil::anykey();
				break;
			case Fight::SKILLS:
				playerTurn = false;
				showSkills(player,enemy, 15, 10);
				
				break;
			case Fight::ITEM:
				playerTurn = false;
				showPotions(player, enemy, 15, 10);
				break;
			case Fight::RUN:
				if (enemy.getLevel() >= 25)
				{
					playerTurn = false;
					std::cout << "You can't run away";
					rlutil::anykey();
					s_turnCount++;
					break;
				}
				else
				{
					int run = generateRandomNumber(1, 10);
					if (run <= 4)
					{
						std::cout << "You have runned successfully";
						s_turnCount = 1;
						rlutil::anykey();
						return Case::RUN;
					}
					else
					{
						playerTurn = false;
						std::cout << "You have failed in running away.";
						rlutil::anykey();
						s_turnCount++;
						break;
					}
				}
				
			}
		}
		else
		{
			gotoxy(1, 14);
			if (enemy.isShocked())
			{
				int chanceToMiss = generateRandomNumber(1, 10);
				if (chanceToMiss <= 5)
				{
					std::cout << "The "<<enemy.getName()<<" is shocked and has missed its attack";
				}
				else
				{
					player.changeHealth(enemy.getAttack() - player.getDefense());
					std::cout << "The " << enemy.getName() << " has attacked you.\n";
					std::cout << "You have taken " << ((enemy.getAttack() - player.getDefense()) > 0 ? (enemy.getAttack() - player.getDefense()) : 1) << " damage\n";
				}
			}
			else
			{
				player.changeHealth(enemy.getAttack() - player.getDefense());
				std::cout << "The " << enemy.getName() << " has attacked you.\n";
				std::cout << "You have taken " << ((enemy.getAttack() - player.getDefense()) > 0 ? (enemy.getAttack() - player.getDefense()) : 1) << " damage\n";
			}
			
			if (player.isDead())
			{
				return Case::DEAD;
			}
			playerTurn = true;
			s_turnCount++;
			rlutil::anykey();
		}

		
	}
}

Interface::Case Interface::movement(MapGeneration &map ,PlayerCharacter &layer, int &location)
{
	rlutil::hidecursor();
	
	int x(0), y(0);
	int i(157);
	while (true)
	{
		if (map.m_map[i].ch == '@')
		{
			x = map.m_map[i].x;
			y = map.m_map[i].y;
			break;
		}
		else i++;
	}
	int tempX{ x }, tempY{ y };
	rlutil::CursorHider curs;
	bool nextLevel = false;
	while (true)
	{
		tempX = x; tempY = y;
		if (kbhit())
		{
			int k = rlutil::getkey();
			if (k == rlutil::KEY_LEFT || k == 'a') --tempX;
			else if (k == rlutil::KEY_RIGHT || k == 'd') ++tempX;
			else if (k == rlutil::KEY_UP || k == 'w') --tempY;
			else if (k == rlutil::KEY_DOWN || k == 's') ++tempY;
			else if (k == rlutil::KEY_ESCAPE) return Case::MENU;
			for (int ii = 0; ii < (2 * map.m_size) * (6 * map.m_size); ii++)
			{
				if ((tempX == map.m_map[ii].x) && (tempY == map.m_map[ii].y))
				{
					if (map.m_map[ii].ch == ' ' || map.m_map[ii].ch == '.' )
					{
						moveCharacter(map, x, y, tempX, tempY);
						x = tempX;
						y = tempY;
						moveMonster(x, y, map);
						break;
					}
					else if (map.m_map[ii].ch == 'X')
					{
						map.m_map[ii].seen = true;
						map.printMap(ii);
						location = ii;
						return Case::TRAP;
					}
					else if (map.m_map[ii].ch == '#')
					{
						map.m_map[ii].seen = true;
						map.printMap(ii);
						tempX = x;
						tempY = y;
						break;
					}
					else if (map.m_map[ii].ch == '$' && map.m_map[ii].seen==false)
					{
						map.m_map[ii].seen = true;
						map.printMap(ii);
						tempX = x;
						tempY = y;
						break;
					}
					else if (map.m_map[ii].ch == '$'&& map.m_map[ii].seen == true)
					{
						location = ii;
						return Case::ITEM;
					}
					else if (map.m_map[ii].ch == '%' && map.m_map[ii].seen == false)
					{
						map.m_map[ii].seen = true;
						map.printMap(ii);
						tempX = x;
						tempY = y;
						break;
					}
					else if (map.m_map[ii].ch == '%'&& map.m_map[ii].seen == true)
					{
						location = ii;
						return Case::POTION;
					}
					else if ((map.m_map[ii].ch == 'M' && map.m_map[ii].seen == false) || (map.m_map[ii].ch == 'N' && map.m_map[ii].seen == false) || (map.m_map[ii].ch == 'O' && map.m_map[ii].seen == false) || (map.m_map[ii].ch == 'B' && map.m_map[ii].seen == false) || (map.m_map[ii].ch == 'S' && map.m_map[ii].seen == false))
					{
						map.printMap(ii);
						tempX = x;
						tempY = y;
						map.m_map[ii].seen = true;
						break;
					}
					else if (map.m_map[ii].ch == 'M' && map.m_map[ii].seen == true)
					{
						location = ii;
						return Case::FIGHT;
					}
					else if (map.m_map[ii].ch == 'N' && map.m_map[ii].seen == true)
					{
						location = ii;
						return Case::FIGHT;
					}
					else if (map.m_map[ii].ch == 'B' && map.m_map[ii].seen == true)
					{
						location = ii;
						return Case::BOSS;
					}
					else if (map.m_map[ii].ch == 'S' && map.m_map[ii].seen == true)
					{
						location = ii;
						return Case::SAVE;
					}
					else if (map.m_map[ii].ch == 'O' && map.m_map[ii].seen == true)
					{
						if(MapGeneration::s_monsterCount <=NUMBER_OF_MONSTERS)
							return Case::NEXT_LEVEL;
						else
						{
							tempX = x;
							tempY = y;
							break;
						}
					}
				}
			}
		}
		
	}
}

void Interface::moveMonster(int x, int y, MapGeneration &map)
{
	struct point
	{
		int x;
		int y;
	};
	point location;
	int X{ x }, Y{ y };
	std::vector<point> monsters;
	for (int i = Y-5; i < Y + 5; i++)
	{
		for (int j = X-5; j < X + 5; j++)
		{
			for (int k = 0; k < map.m_size*map.m_size * 12; k++)
			{
				if (map.m_map[k].x == j && map.m_map[k].y == i)
				{
					if (map.m_map[k].ch == 'N')
					{
						location.x = j;
						location.y = i;
						monsters.push_back(location);
					}
				}
			}
		}
	}
	int xx = 75, yy = 13;
	for (auto const &element : monsters)
	{
		bool right{ false }, left{ false }, up{ false }, down{ false };
		if (element.x > x)
			left = true;
		else if (element.x < x)
			right = true;
		if (element.y > y)
			up = true;
		else if (element.y < y)
			down = true;
		int tempX{ element.x }, tempY{ element.y };
		if (up)
		{
			if (right)
				tempX++;
			else if (left)
				tempX--;
			tempY--;
		}
		else if (down)
		{
			if (right)
				tempX++;
			else if (left)
				tempX--;
			tempY++;
		}
		for (int k = 0; k < map.m_size*map.m_size * 12; k++)
		{
			if (map.m_map[k].x == tempX && map.m_map[k].y == tempY)
			{
				if(map.m_map[k].ch==' ' || map.m_map[k].ch=='.')
					moveCharacter(map, element.x, element.y, tempX, tempY, 'N');
			}
		}
		
		
	}

}

void Interface::moveCharacter(MapGeneration &map, int startX, int startY, int endX, int endY, char ch)
{
	for (int ii = 0; ii < (6 * map.m_size * 2 * map.m_size); ii++)
	{
		if (startX == map.m_map[ii].x && startY == map.m_map[ii].y)
		{
			if (ch == '@')
			{
				map.m_map[ii].ch = '.';
				map.m_map[ii].seen = true;
			}
			
			else
			{
				map.m_map[ii].ch = ' ';
				map.m_map[ii].seen = false;
			}
				
			map.printMap(ii);
		}

		if (endX == map.m_map[ii].x && endY == map.m_map[ii].y)
		{
			map.m_map[ii].ch = ch;
			map.printMap(ii);
		}
	}
}

void Interface::printInfo()
{
	gotoxy(75, 4);
	std::cout << "Level: " << MapGeneration::s_level;
	gotoxy(75, 5);
	std::cout << "Monster count :" << MapGeneration::s_monsterCount;
}

void Interface::clearLocation(MapGeneration &map, int location)
{
	map.m_map[location].ch = ' ';
}

void Interface::nextLevel(MapGeneration &map)
{
	
	map.s_level++;
	if (map.s_level == 10 * (Boss::s_encounter + 1) )
		map.bossLevel(map.m_size);
	else if (map.s_level > 40)
	{
		rlutil::cls();
		std::cout << "Congratulations!\n";
		std::cout << "You have completed the trial version if you want to continue playing please purchase the full version.";
		rlutil::anykey();
		exit(1);
	}
	else
		map.setMap(map.m_size);
}

void Interface::gotItem(PlayerCharacter &player, Item &item)
{
	gotoxy(75, 7);
	std::cout << "You found an item! " << item.m_name << " found!";
	player.setMaxHealth(player.getMaxHealth() + item.m_health);
	player.changeHealth(item.m_health, '+');
	player.setMaxAttack(player.getMaxAttack() + item.m_attack);
	player.setAttack(player.getMaxAttack());
	player.setMaxDefense(player.getMaxDefense() + item.m_defense);
	player.setDefense(player.getMaxDefense());

	gotoxy(75, 8);
	if (item.m_health > 0)
		std::cout << "Health +" << item.m_health;
	if (item.m_attack > 0)
		std::cout << "Attack +" << item.m_attack;
	if (item.m_defense > 0)
		std::cout << "Defense +" << item.m_defense;
	rlutil::anykey();
}

void Interface::gotTrapped(PlayerCharacter &player, Trap &trap)
{
	gotoxy(75, 7);
	std::cout << "You activated a " << trap.getType() << " trap!";
	gotoxy(75, 8);
	if (trap.getType() == "Fire")
	{
		player.setBurning(3);
		std::cout << "You have been set on fire.";
	}
	else if (trap.getType() == "Poisonous")
	{
		player.setPoisoned(5);
		std::cout << "You have been poisoned.";
	}
	else if (trap.getType() == "Lacerating")
	{
		player.setBleeding(3);
		std::cout << "You have started bleeding.";
	}
	rlutil::anykey();
}

void Interface::gotPotion(PlayerCharacter &player, Potion &potion)
{
	rlutil::hidecursor();
	gotoxy(75, 7);
	std::cout << "You found a potion!";
	gotoxy(75, 8);
	std::cout<< potion.getName() << " potion found!";
	player.addPotion(potion);
	rlutil::anykey();
}

Interface::Menu Interface::menu()
{
	int initialY{ 7 }, finalY{ initialY };
	gotoxy(75, initialY);
	std::cout << "Continue";
	gotoxy(75, ++finalY);
	std::cout << "Items";
	gotoxy(75, ++finalY);
	std::cout << "Stats";
	gotoxy(75, ++finalY);
	std::cout << "Restart Level";
	gotoxy(75, ++finalY);
	std::cout << "Quit";

	int choice{ 0 };
	rlutil::CursorHider curs;
	int x{ 90 }, y{ 7 };
	gotoxy(x, y); std::cout << "*";
	
	while (true)
	{
		if (kbhit())
		{
			gotoxy(x, y); std::cout << " ";
			int k = rlutil::getkey();
			if (k == rlutil::KEY_UP || k == 'w')
			{
				if (y == initialY)
				{
					y = finalY;
					choice = static_cast<int>(Menu::MAX_CASE) - 1;
				}
				else
				{
					y--;
					choice--;
				}

			}
			else if (k == rlutil::KEY_DOWN || k == 's')
			{
				if (y == finalY)
				{
					y = initialY;
					choice = static_cast<int>(Menu::CONTINUE);
				}
				else
				{
					y++;
					choice++;
				}
			}
			else if (k == rlutil::KEY_ENTER || k == 'e') break;
			gotoxy(x, y); std::cout << "*";
		}
	}
	return static_cast<Interface::Menu>(choice);
}

void Interface::showPotions(PlayerCharacter &player, Enemy &enemy, int x, int y)
{
	if (showPotions(player, x, y))
		fight(player, enemy);
}

bool Interface::showPotions(PlayerCharacter &player,int x , int y)
{
	rlutil::CursorHider curs;
	int shown{ 0 };
	for (int i = 0; i < 10; i++)
	{
		shown++;
		gotoxy(x, y++);
		std::cout << "(" << shown << ")" << player.ptr[i]->getName();
	}
	if (shown == 0)
	{
		gotoxy(x, y);
		std::cout << "You have no potions!";
	}
	if (shown > 0)
	{
		int choice{ 0 };

		y = y - shown; x = x + 15;
		int initialY{ y }, finalY{ initialY + shown - 1 };

		gotoxy(x, y); std::cout << "*";
		while (true)
		{
			if (kbhit())
			{
				gotoxy(x, y); std::cout << " ";
				int k = rlutil::getkey();
				if (k == rlutil::KEY_UP || k == 'w')
				{
					if (y == initialY)
					{
						y = finalY;
						choice = 9;
					}
					else
					{
						y--;
						choice--;
					}

				}
				else if (k == rlutil::KEY_DOWN || k == 's')
				{
					if (y == finalY)
					{
						y = initialY;
						choice = 0;
					}
					else
					{
						y++;
						choice++;
					}
				}
				else if (k == rlutil::KEY_ENTER || k == 'e')
				{
					gotoxy(x, y); std::cout << "*";
					break;
				}
				gotoxy(x, y); std::cout << "*";
			}
		}
		gotoxy(x + 10, y);
		std::cout << "Use";
		gotoxy(x + 10, y + 1);
		std::cout << "Discard";
		gotoxy(x + 10, y + 2);
		std::cout << "Cancel";
		x = x + 18;
		int initialY2{ y }, finalY2{ initialY2 + 2 };
		int option{ 0 };
		gotoxy(x, y); std::cout << "*";
		while (true)
		{
			if (kbhit())
			{
				gotoxy(x, y); std::cout << " ";
				int k = rlutil::getkey();
				if (k == rlutil::KEY_UP || k == 'w')
				{
					if (y == initialY2)
					{
						y = finalY2;
						option = static_cast<int>(Items::MAX_CASE) - 1;
					}
					else
					{
						y--;
						option--;
					}

				}
				else if (k == rlutil::KEY_DOWN || k == 's')
				{
					if (y == finalY2)
					{
						y = initialY2;
						option = static_cast<int>(Items::USE);
					}
					else
					{
						y++;
						option++;
					}
				}
				else if (k == rlutil::KEY_ENTER || k == 'e')
				{
					gotoxy(x, y); std::cout << "*";
					break;
				}
				gotoxy(x, y); std::cout << "*";
			}
		}
		if (option == static_cast<int>(Items::USE))
		{
			s_turnCount++;
			usePotion(player, choice);

		}
		else if (option == static_cast<int>(Items::DISCARD))
		{
			player.removePotion(choice);
		}
		else if (option == static_cast<int>(Items::CANCEL))
		{
			return true;
		}
	}
	return false;
}

void Interface::usePotion(PlayerCharacter &player, int x)
{
	if (player.ptr[x]->getName() == "HEALING")
	{
		player.changeHealth(player.getMaxHealth()/4, '+');
		player.removePotion(x);
	}
	else if (player.ptr[x]->getName() == "ANTIDOTE")
	{
		player.setPoisoned(0);
		player.removePotion(x);
	}
	else if (player.ptr[x]->getName() == "COOLING")
	{
		player.setBurning(0);
		player.removePotion(x);
	}
	else if (player.ptr[x]->getName() == "BLOOD")
	{
		player.setBleeding(0);
		player.removePotion(x);
	}
	
}

void Interface::checkStatus(Character &character)
{
	int y{ 2 };
	if (character.isBleeding())
	{
		gotoxy(27, ++y);
		std::cout << character.getName() << " is bleeding and have lost 1 attack ";
		character.changeAttack(1, '-');
	}
	else
	{
		character.setAttack(character.getMaxAttack());
	}
	if (character.isBurning())
	{
		gotoxy(27, ++y);
		std::cout << character.getName() << " is on fire and have lost 1 defense ";
		character.changeDefense(1, '-');
	}
	else
	{
		character.setDefense(character.getMaxDefense());
	}
	if (character.isPoisoned())
	{
		gotoxy(27, ++y);
		std::cout << character.getName() << " is poisoned and have lost 1 health ";
		character.changeHealth(character.getMaxHealth() *0.03);
	}
}

void Interface::showSkills(PlayerCharacter &player,Enemy &enemy, int x, int y)
{
	int iniX{ x }, iniY{ y };
	rlutil::CursorHider curs;
	for (int i = 0; i < No_Skills; i++)
	{
		gotoxy(x, y++);
		std::cout << "(" << i << ")" << Skills[i];
	}

	int choice{ 0 };

	y = y - No_Skills; x = x + 18;
	int initialY{ y }, finalY{ initialY + No_Skills - 1 };

	gotoxy(x, y); std::cout << "*";
	while (true)
	{
		if (kbhit())
		{
			gotoxy(x, y); std::cout << " ";
			int k = rlutil::getkey();
			if (k == rlutil::KEY_UP || k == 'w')
			{
				if (y == initialY)
				{
					y = finalY;
					choice = static_cast<int>(Interface::Skills::MAX_CASE)-1;
				}
				else
				{
					y--;
					choice--;
				}

			}
			else if (k == rlutil::KEY_DOWN || k == 's')
			{
				if (y == finalY)
				{
					y = initialY;
					choice = static_cast<int>(Interface::Skills::QUICK_ATTACK);
				}
				else
				{
					y++;
					choice++;
				}
			}
			else if (k == rlutil::KEY_ENTER || k == 'e')
			{
				gotoxy(x, y); std::cout << "*";
				break;
			}
			gotoxy(x, y); std::cout << "*";
		}
	}
	gotoxy(x + 10, y);
	std::cout << "Use";
	gotoxy(x + 10, y + 1);
	std::cout << "Cancel";
	x = x + 18;
	int initialY2{ y }, finalY2{ initialY2 + 1 };
	int option{ 0 };
	gotoxy(x, y); std::cout << "*";
	while (true)
	{
		if (kbhit())
		{
			gotoxy(x, y); std::cout << " ";
			int k = rlutil::getkey();
			if (k == rlutil::KEY_UP || k == 'w')
			{
				if (y == initialY2)
				{
					y = finalY2;
					option = static_cast<int>(Interface::SkillsChoice::MAX_CASE) - 1;
				}
				else
				{
					y--;
					option--;
				}

			}
			else if (k == rlutil::KEY_DOWN || k == 's')
			{
				if (y == finalY2)
				{
					y = initialY2;
					option = static_cast<int>(Interface::SkillsChoice::USE);
				}
				else
				{
					y++;
					option++;
				}
			}
			else if (k == rlutil::KEY_ENTER || k == 'e')
			{
				gotoxy(x, y); std::cout << "*";
				break;
			}
			gotoxy(x, y); std::cout << "*";
		}
	}
	if (option == static_cast<int>(Interface::SkillsChoice::USE))
	{
		s_turnCount++;
		useSkill(enemy, choice);
	}
	if (option == static_cast<int>(Interface::SkillsChoice::CANCEL))
	{
		rlutil::cls();
		fight(player, enemy);
	}
	
}

void Interface::useSkill(Enemy &enemy, int skill)
{
	int chance_to_hit{ 0 };

	switch (skill)
	{
	case static_cast<int>(Interface::Skills::QUICK_ATTACK) :
		chance_to_hit = generateRandomNumber(1, 10);
		if (chance_to_hit < 9)
		{
			enemy.changeHealth(enemy.getMaxHealth() * 0.25);
			std::cout << "You have dealt " << enemy.getMaxHealth() * 0.25 << " damage to the " << enemy.getName() << '\n';
		}
		else
			std::cout << "You have missed\n";
		break;
	case static_cast<int>(Interface::Skills::NORMAL_ATTACK) :
		chance_to_hit = generateRandomNumber(1, 10);
		if (chance_to_hit < 6)
		{
			enemy.changeHealth(enemy.getMaxHealth() * 0.45);
			std::cout << "You have dealt " << enemy.getMaxHealth() * 0.45 << " damage to the " << enemy.getName() << '\n';
		}
		else
			std::cout << "You have missed\n";
		break;
	case static_cast<int>(Interface::Skills::STRONG_ATTACK) :
		chance_to_hit = generateRandomNumber(1, 10);
		if (chance_to_hit < 3)
		{
			enemy.changeHealth(enemy.getMaxHealth() * 0.7);
			std::cout << "You have dealt " << enemy.getMaxHealth() * 0.7 << " damage to the " << enemy.getName() << '\n';
		}
		else
			std::cout << "You have missed\n";
		break;
	}
	rlutil::anykey();
}

void Interface::mainMenu()
{
	rlutil::CursorHider curs;
	gotoxy(50, 3);
	std::cout << "The Dungeon";
	gotoxy(50, 5);
	std::cout << "New Game";
	gotoxy(50, 6);
	std::cout << "Load Game";
	gotoxy(50, 7);
	std::cout << "Quit Game";
	int initialY{ 5 }, finalY{ initialY + 2 };
	int option{ 0 };
	int x{ 60 }, y{ initialY };
	gotoxy(x, y); std::cout << "*";
	while (true)
	{
		if (kbhit())
		{
			gotoxy(x, y); std::cout << " ";
			int k = rlutil::getkey();
			if (k == rlutil::KEY_UP || k == 'w')
			{
				if (y == initialY)
				{
					y = finalY;
					option = static_cast<int>(Interface::MainMenu::MAX_CASE) - 1;
				}
				else
				{
					y--;
					option--;
				}

			}
			else if (k == rlutil::KEY_DOWN || k == 's')
			{
				if (y == finalY)
				{
					y = initialY;
					option = static_cast<int>(Interface::MainMenu::NEW_GAME);
				}
				else
				{
					y++;
					option++;
				}
			}
			else if (k == rlutil::KEY_ENTER || k == 'e')
			{
				gotoxy(x, y); std::cout << "*";
				break;
			}
			gotoxy(x, y); std::cout << "*";
		}
	}

	switch (option)
	{
	case static_cast<int>(Interface::MainMenu::NEW_GAME) :
		newGame();
		break;
	case static_cast<int>(Interface::MainMenu::LOAD_GAME) :
		loadGame();
		break;
	case static_cast<int>(Interface::MainMenu::QUIT_GAME) :
		exit(1);
		break;
	}
}

void Interface::newGame()
{
	rlutil::cls();
	rlutil::showcursor();
	gotoxy(50, 5);
	std::cout << "Input your name";
	gotoxy(50, 6);
	std::string name;
	std::cin >> name;
	rlutil::cls();
	PlayerCharacter player(name);
	MapGeneration map(10);
	Game(player, map);
	
}

void Interface::loadGame()
{
	rlutil::cls();
	std::ifstream load("Save File.txt");
	if (!load)
	{
		gotoxy(40, 5);
		std::cerr << "There is no save file";
		rlutil::anykey();
		exit(1);
	}
	else 
	{
		std::string name;
		std::getline(load, name);
		PlayerCharacter player(name);
		double data;
		load >> data;
		player.setLevel(data);
		load >> data;
		player.setExperience(data);
		load >> data;
		player.setMaxHealth(data);
		load >> data;
		player.setHealth(data);
		load >> data;
		player.setMaxAttack(data);
		player.setAttack(player.getMaxAttack());
		load >> data;
		player.setMaxDefense(data);
		player.setDefense(player.getMaxDefense());

		MapGeneration map(10);

		load >> data;
		MapGeneration::s_level = data;
		if (MapGeneration::s_level >= 40)
		{
			rlutil::cls();
			gotoxy(40, 5);
			std::cout << "You have already cleared the game.";
			gotoxy(40, 6);
			std::cout << "Please choose the New Game option next time if you want to play";
			rlutil::anykey();
			exit(1);
		}
		load >> data;
		Boss::s_encounter = data;
		Game(player, map);
	}
}

void Interface::save(PlayerCharacter &player)
{
	std::ofstream saveFile("Save File.txt");

	saveFile << player.getName()<<'\n';
	saveFile << player.getLevel() << '\n';
	saveFile << player.getExperience() << '\n';
	saveFile << player.getMaxHealth() << '\n';
	saveFile << player.getHealth() << '\n';
	saveFile << player.getMaxAttack() << '\n';
	saveFile << player.getMaxDefense() << '\n';
	saveFile << MapGeneration::s_level +1<< '\n';
	saveFile << Boss::s_encounter << '\n';
	

}

void Interface::Game(PlayerCharacter &player,MapGeneration &map)
{
	
	if (TEST_MODE)
		player.TestMode();
	while (true)
	{
		if (SHOW_MAP)
			map.showMap();
		int location = 0;
		bool gameOver = false, restartLevel = false;
		printInfo();
		switch (movement(map, player, location))
		{
		case Interface::Case::FIGHT:
			switch (fight(player, Enemy::getRandomMonster()))
			{
			case Interface::Case::WON:
				clearLocation(map, location);
				break;
			case Interface::Case::RUN:
				break;
			case Interface::Case::DEAD:
				std::cout << "You are Dead.\nGame Over\n";
				gameOver = true;
				break;
			default:
				break;
			}
			break;
		case Interface::Case::BOSS:
			switch (fight(player, Boss::getBoss()))
			{
			case Interface::Case::WON:
				clearLocation(map, location);
				Boss::s_encounter++;
				if (Boss::s_encounter == 4)
					Boss::s_encounter = 0;
				break;
			case Interface::Case::DEAD:
				std::cout << "You are Dead.\nGame Over\n";
				gameOver = true;
				break;
			default:
				break;
			}
			break;
		case Interface::Case::NEXT_LEVEL:
			nextLevel(map);
			break;
		case Interface::Case::ITEM:
			gotItem(player, Item::getRandomItem());
			clearLocation(map, location);
			break;
		case Interface::Case::TRAP:
			gotTrapped(player, Trap::getRandomTrap());
			clearLocation(map, location);
			break;
		case Interface::Case::POTION:
			gotPotion(player, Potion::getRandomPotion());
			clearLocation(map, location);
			break;
		case Interface::Case::MENU:
			switch (menu())
			{
			case Interface::Menu::CONTINUE:
				break;
			case Interface::Menu::STATS:
				player.getStats(75, 13);
				rlutil::anykey();
				break;
			case Interface::Menu::ITEMS:
				showPotions(player, 75, 13);
				break;
			case Interface::Menu::RESTART_LEVEL:
				restartLevel = true;
				break;
			case Interface::Menu::QUIT:
				exit(1);
			}
			break;
		case Interface::Case::SAVE:
			save(player);
			clearLocation(map, location);
			break;
		}
		if (gameOver)
			break;
		if (restartLevel)
			map.restartLevel();
		rlutil::cls();
		map.rePrintMap();
	}
}