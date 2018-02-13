#include "PlayerCharacter.h"
int PlayerCharacter::s_exp = 0;
int PlayerCharacter::s_level = 1;
int PlayerCharacter::s_multiplier = 1;
PlayerCharacter::PlayerCharacter(std::string name)
	:Character{name, 25, 3, 2 }
{
	setPotions();
	
}

void PlayerCharacter::setLevel(int level)
{
	s_level = level;
}

void PlayerCharacter::changeLevel(int level, char sign)
{
	if (level > 0)
	{
		if (sign == '+')
			s_level += level;
		else if (sign == '-')
			s_level -= level;
	}
}

int PlayerCharacter::getLevel()
{
	return s_level;
}

void PlayerCharacter::setExperience(int exp)
{
	s_exp = exp;
}

int PlayerCharacter::getExperience()
{
	return s_exp;
}

void PlayerCharacter::gainExperience(int exp)
{
	s_exp += exp;
}

bool PlayerCharacter::levelUp()
{
	if (s_exp >= s_level * s_multiplier + 5)
	{
		s_multiplier++;
		changeLevel(1);
		setMaxHealth(getMaxHealth() + 5);
		setHealth(getMaxHealth());
		setMaxAttack(getMaxAttack() + 1);
		setAttack(getMaxAttack());
		if(s_level%2==0)
			setMaxDefense(getMaxDefense() + 1);
		setDefense(getMaxDefense());
		setExperience(0);
		return true;
	}
	else return false;
}

void PlayerCharacter::getStats(int x, int y)
{
	gotoxy(x, y);
	std::cout << "Player stats: " << '\n';
	gotoxy(x, ++y);
	std::cout << "Name: " << getName();
	gotoxy(x, ++y);
	std::cout << "Level: " << getLevel();
	gotoxy(x, ++y);
	std::cout << "Experience: " << getExperience()<<"/"<<s_level*s_multiplier+5;
	gotoxy(x, ++y);
	std::cout << "Health: " << getHealth()<<"/"<<getMaxHealth();
	gotoxy(x, ++y);
	std::cout << "Attack: " << getAttack();
	gotoxy(x, ++y);
	std::cout << "Defense: " << getDefense();
	
	
}

void PlayerCharacter::setPotions()
{
	for (int i = 0; i < 10; i++)
	{
		ptr[i] = new Potion;
	}
}

void PlayerCharacter::addPotion(Potion &potion)
{
	for (int i = 0; i < 10; i++)
	{
		if (ptr[i]->getIfEmpty() == true)
		{
			ptr[i]->setName(potion.getName());
			ptr[i]->setEmpty(false);
			break;
		}
	}
}

void PlayerCharacter::removePotion(int x)
{
	ptr[x]->setName("Empty space");
	ptr[x]->setEmpty(true);
}

void PlayerCharacter::TestMode()
{
	setAttack(9999);
	setMaxAttack(9999);
	setMaxDefense(9999);
	setDefense(9999);
	setMaxHealth(99999);
	setHealth(99999);
}