#include "Status.h"

void Status::setBurning(int duration)
{
	m_burningDuration = duration;
}

bool Status::isBurning()
{
	if (m_burningDuration > 0)
	{
		m_burningDuration--;
		return true;
	}
	else
		return false;
}

void Status::setFrozen(int duration)
{
	m_frozenDuration = duration;
}

bool Status::isFrozen()
{
	if (m_frozenDuration > 0)
	{
		m_frozenDuration--;
		return true;
	}
	else
		return false;
}

void Status::setPoisoned(int duration)
{

	m_poisonedDuration = duration;
}

bool Status::isPoisoned()
{
	if (m_poisonedDuration > 0)
	{
		m_poisonedDuration--;
		return true;
	}
	else
		return false;
}

void Status::setShocked(int duration)
{

	m_shockedDuration = duration;
}

bool Status::isShocked()
{
	if (m_shockedDuration > 0)
	{
		m_shockedDuration--;
		return true;
	}
	else
		return false;
}

void Status::setBleeding(int duration)
{
	m_bleedingDuration = duration;
}

bool Status::isBleeding()
{
	if (m_bleedingDuration > 0)
	{
		m_bleedingDuration--;
		return true;
	}
	else
		return false;
}