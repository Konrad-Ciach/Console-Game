#pragma once
#include"Status.h"
#include<iostream>
#include<string>
#include"rlutil.h"

class Character: public Status
{
protected:
	std::string m_name;
	double m_maxHealth;
	double m_health;
	double m_maxAttack;
	double m_attack;
	double m_maxDefense;
	double m_defense;
	Character(std::string name ,double health, double attack, double defense)
		: m_name{ name } , m_maxHealth {health}, m_health(m_maxHealth), m_attack{ attack }, m_defense{ defense }, m_maxAttack{ attack }, m_maxDefense{ defense }
	{
	}

public:
	std::string getName();

	void setMaxHealth(double amount);
	double getMaxHealth();
	void setHealth(double health);
	void changeHealth(double health , char sign = '-');
	double getHealth();

	void setMaxAttack(double attack);
	double getMaxAttack();
	void setAttack(double attack);
	void changeAttack(double attack, char sign = '+');
	double getAttack();

	void setMaxDefense(double defense);
	double getMaxDefense();
	void setDefense(double defense);
	void changeDefense(double defense, char sign = '+');
	double getDefense();

	virtual void getStats(int x, int y)=0;
	bool isDead();

};