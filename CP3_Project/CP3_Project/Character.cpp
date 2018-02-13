#include "Character.h"


std::string Character::getName()
{
	return m_name;
}

void Character::setMaxHealth(double amount)
{
	m_maxHealth = amount;
}

double Character::getMaxHealth()
{
	return m_maxHealth;
}

void Character::setHealth(double health)
{
	m_health = health;
}

void Character::changeHealth(double health, char sign)
{
	if (health > 0)
	{
		if (sign == '+')
		{
			if (m_health + health > getMaxHealth())
				m_health = getMaxHealth();
			else
				m_health += health;
		}
		else if (sign == '-')
			m_health -=health;
	}
	else if (health <= 0)
	{
		m_health--;
	}
}

double Character::getHealth()
{
	return m_health;
}

void Character::setMaxAttack(double attack)
{
	m_maxAttack = attack;
}

double Character::getMaxAttack()
{
	return m_maxAttack;
}

void Character::setAttack(double attack)
{
	m_attack = attack;
}

void Character::changeAttack(double attack, char sign)
{
	if (attack > 0)
	{
		if (sign == '+')
			m_attack +=attack;
		else if (sign == '-')
		{
			if (m_attack - attack > 0)
			{
				m_attack -= attack;
			}
			else
				m_attack = 1;
		}
			
	}
}

double Character::getAttack()
{
	return m_attack;
}

void Character::setMaxDefense(double defense)
{
	m_maxDefense = defense;
}

double Character::getMaxDefense()
{
	return m_maxDefense;
}

void Character::setDefense(double defense)
{
	m_defense = defense;
}

void Character::changeDefense(double defense, char sign)
{
	if (defense > 0)
	{
		if (sign == '+')
			m_defense +=defense;
		else if (sign == '-')
		{
			if (m_defense - defense > 0)
			{
				m_defense -= defense;
			}
			else
				m_defense = 0;
		}
	}
}

double Character::getDefense()
{
	return m_defense;
}

bool Character::isDead()
{
	if (m_health <= 0)
		return true;
	else return false;
}

