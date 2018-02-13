#pragma once
#include<string>
#include<ctime>
class Potion
{
private:
	std::string m_name="Empty space";
	bool m_used=false;
	bool m_empty=true;
	
public:

	enum Type
	{
		HEALING,
		ANTIDOTE,
		COOLING,
		BLOOD,
		MAX_TYPE
	};
	static std::string name[MAX_TYPE];
	static Potion getRandomPotion();
	Potion(Type type);
	Potion();
	std::string getName();
	void setName(std::string name);
	void setUsed(bool state);
	bool getIfUsed();
	void setEmpty(bool state);
	bool getIfEmpty();
};