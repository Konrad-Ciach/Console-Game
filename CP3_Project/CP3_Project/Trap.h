#pragma once
#include<string>
#include<ctime>

class Trap
{
private:
	std::string m_type;
public:
	enum Type
	{
		FIRE,
		POISONOUS,
		LACERATING,
		MAX_TYPE
	};
	Trap(int x);
	static std::string trap[MAX_TYPE];
	static Trap getRandomTrap();
	std::string getType();
};