#pragma once


class Status
{
protected:
	int m_burningDuration = 0;
	int m_frozenDuration = 0;
	int m_poisonedDuration = 0;
	int m_shockedDuration = 0;
	int m_bleedingDuration = 0;

	Status()
	{

	}

public:
	void setBurning(int duration);
	bool isBurning();
	void setFrozen(int duration);
	bool isFrozen();
	void setPoisoned(int duration);
	bool isPoisoned();
	void setShocked(int duration);
	bool isShocked();
	void setBleeding(int duration);
	bool isBleeding();
};