#include "MapGeneration.h"
#include <windows.h>
#include<iostream>
#include <cstdlib>
#include <ctime> 
#include"rlutil.h"

int MapGeneration::s_level = 1;
int MapGeneration::s_monsterCount = 0;

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

MapGeneration::MapGeneration(int size)
{
	setSize(size);
}

void MapGeneration::setSize(int size)
{
	m_size = size;
	m_map = new MapCoordinates[(2*m_size) * (6*m_size)];
	setMap(m_size);
}

MapGeneration::~MapGeneration()
{
	delete[] m_map;
}

void MapGeneration::setMap(int size)
{
	int i = 0;
	s_monsterCount = 0;
	for (int xx = 10; xx < (7 * size); xx = xx + 59)
	{
		for (int yy = 3; yy <= (2 * size + 2); yy++)
		{

			m_map[i].x = xx;
			m_map[i].y = yy;
			m_map[i].ch = '|';
			m_map[i].seen = true;
			printMap(i);
			++i;
		}
	}
		
	for (int yy = 3; yy <= (2 * size + 2); yy = yy + 19)
	{
		for (int xx = 11; xx < (7 * size - 1); xx++)
		{
			m_map[i].x = xx;
			m_map[i].y = yy;
			m_map[i].ch = '-';
			m_map[i].seen = true;
			printMap(i);
			++i;
		}
	}

	for (int xx = 11; xx < (7 * size - 1); xx++)
	{
		for (int yy = 4; yy <= (2 * size + 1); yy++)
		{
			
			m_map[i].x = xx;
			m_map[i].y = yy;
			m_map[i].ch = ' ';
			++i; 
		}
	}

	srand(static_cast<unsigned int>(time(0)));
	rand();

	for (int jj = 0; jj < 0.65*i; ++jj)
	{
		int num = getRandomNumber(0, i);
		if (m_map[num].ch == ' ')
		{
			m_map[num].ch = '#';
			m_map[num].seen = false;
		}
	}
	
	int heroPosition = getRandomNumber(157, i);
	m_map[heroPosition].ch = '@';
	printMap(heroPosition);

	int gatePosition = getRandomNumber(157, i);
	m_map[gatePosition].ch = 'O';	
	m_map[gatePosition].seen = false;

	for (int i = 0; i < 3; i++)
	{
		int randomPosition;
		while (true)
		{
			randomPosition = getRandomNumber(157, i);
			if (randomPosition != heroPosition && randomPosition != gatePosition)
				break;
		}
		creatingDungeon(randomPosition);
		
	}
	creatingDungeon(heroPosition);
	creatingDungeon(gatePosition);
	
	s_monsterCount = 0;
		
	int numberOfItems = getRandomNumber(1, 5);
	while (numberOfItems > 0)
	{
		int randomPlace = getRandomNumber(157, i);
		if (m_map[randomPlace].ch == ' ')
		{
			m_map[randomPlace].ch = '$';
			numberOfItems--;	m_map[randomPlace].seen = false;	
		}
	}

	while (s_monsterCount<30)
	{
		int randomPlace = getRandomNumber(157, i);
		if (m_map[randomPlace].ch == ' ')
		{
			m_map[randomPlace].ch = 'M';
			m_map[randomPlace].seen = false;
			s_monsterCount++; m_map[randomPlace].seen = false;	
		}	
	}
	while (s_monsterCount<40)
	{
		int randomPlace = getRandomNumber(157, i);
		if (m_map[randomPlace].ch == ' ')
		{
			m_map[randomPlace].ch = 'N';
			m_map[randomPlace].seen = false;
			s_monsterCount++; m_map[randomPlace].seen = false;
		}
	}

	int numberOfTraps = getRandomNumber(2, 4);
	while (numberOfTraps > 0)
	{
		int randomPlace = getRandomNumber(157, i);
		if (m_map[randomPlace].ch == ' ')
		{
			m_map[randomPlace].ch = 'X';
			numberOfTraps--;	m_map[randomPlace].seen = false;   
		}
	}

	

	int numberOfPotions = getRandomNumber(5, 10);
	while (numberOfPotions > 0)
	{
		int randomPlace = getRandomNumber(157, i);
		if (m_map[randomPlace].ch == ' ')
		{
			m_map[randomPlace].ch = '%';
			numberOfPotions--;	 m_map[randomPlace].seen = false;	
		}
	}
	
}

void MapGeneration::printMap(int placeInArray)
{
	rlutil::saveDefaultColor();
	gotoxy(m_map[placeInArray].x, m_map[placeInArray].y);
	if (m_map[placeInArray].ch == '#')
		rlutil::setColor(2);
	else if (m_map[placeInArray].ch == 'O')
		rlutil::setColor(13);
	else if (m_map[placeInArray].ch == 'M')
		rlutil::setColor(12);
	else if (m_map[placeInArray].ch == 'N')
		rlutil::setColor(4);
	else if (m_map[placeInArray].ch == '$')
		rlutil::setColor(14);
	else if (m_map[placeInArray].ch == 'X')
		rlutil::setColor(9);
	else if (m_map[placeInArray].ch == '%')
		rlutil::setColor(11);
	else if (m_map[placeInArray].ch == 'B')
		rlutil::setColor(12);
	else if (m_map[placeInArray].ch == 'S')
		rlutil::setColor(5);
	std::cout << m_map[placeInArray].ch;
	rlutil::resetColor();
}

void MapGeneration::rePrintMap()
{
	for (int ii = 0; ii < 6 * m_size * 2 * m_size; ii++)
	{
		if (m_map[ii].seen == true)
			printMap(ii);
		if (m_map[ii].ch == '@')
			printMap(ii);
	}
}

void MapGeneration::restartLevel()
{
	rlutil::cls();
	setMap(m_size);
}

void MapGeneration::bossLevel(int size)
{
	clearMap();
	int i = 0;
	for (int xx = 10; xx < (7 * size); xx = xx + 59)
	{
		for (int yy = 3; yy <= (2 * size + 2); yy++)
		{

			m_map[i].x = xx;
			m_map[i].y = yy;
			m_map[i].ch = '|';
			m_map[i].seen = true;
			printMap(i); ++i;
		}
	}
	
	for (int yy = 3; yy <= (2 * size + 2); yy = yy + 19)
	{
		for (int xx = 11; xx < (7 * size - 1); xx++)
		{
			m_map[i].x = xx;
			m_map[i].y = yy;
			m_map[i].ch = '-';
			m_map[i].seen = true;
			printMap(i); ++i;
		}
	}
	int ii = i;
	for (int xx = 11; xx < (7 * size - 1); xx++)
	{
		for (int yy = 4; yy <= (2 * size + 1); yy++)
		{

			m_map[i].x = xx;
			m_map[i].y = yy;
			m_map[i].ch = ' ';
			++i;
		}
	}

	for (int xx = 38; xx <= 42; xx = xx + 4)
	{
		for (int yy = 4; yy <= (2 * size + 1); yy++)
		{
			m_map[ii].x = xx;
			m_map[ii].y = yy;
			m_map[ii].ch = '#';	m_map[ii].seen = true;
			printMap(ii);
			
			ii++;
		}
	}
	m_map[ii].x = 40;
	m_map[ii].y = 5;
	m_map[ii].ch = 'O'; 
	ii++;

	m_map[ii].x = 41;
	m_map[ii].y = 6;
	m_map[ii].ch = 'S';
	ii++;


	m_map[ii].x = 39;
	m_map[ii].y = 7;
	m_map[ii].ch = '#';
	
	ii++;

	m_map[ii].x = 41;
	m_map[ii].y = 7;
	m_map[ii].ch = '#'; 
	
	ii++;

	m_map[ii].x = 40;
	m_map[ii].y = 7;
	m_map[ii].ch = 'B';
	
	ii++;

	m_map[ii].ch = '@';
	m_map[ii].x = 40;
	m_map[ii].y = 21;
	printMap(ii);
	s_monsterCount = 1;
	
}

void MapGeneration::clearMap()
{
	for (int i = 0; i < (2 * m_size) * (6 * m_size); i++)
	{
		m_map[i].ch = ' ';
		m_map[i].seen = false;
	}
}

void MapGeneration::showMap()
{
	for (int i = 0; i < (2 * m_size) * (6 * m_size); i++)
	{
		printMap(i);
	}
}

void MapGeneration::creatingDungeon(int position)
{
	int space = 1;
	while (true)
	{
		for (int j = 0; j < (2 * m_size) * (6 * m_size); j++)
		{
			if (m_map[position].x + space == m_map[j].x && m_map[position].y == m_map[j].y)
			{
				if (m_map[j].ch == '#')
				{
					m_map[j].ch = ' ';
				}
			}
		}
		for (int j = 0; j < (2 * m_size) * (6 * m_size); j++)
		{
			if (m_map[position].x - space == m_map[j].x && m_map[position].y == m_map[j].y)
			{
				if (m_map[j].ch == '#')
				{
					m_map[j].ch = ' ';
				}
			}
		}
		for (int j = 0; j < (2 * m_size) * (6 * m_size); j++)
		{
			if (m_map[position].y + space == m_map[j].y && m_map[position].x == m_map[j].x)
			{
				if (m_map[j].ch == '#')
				{
					m_map[j].ch = ' ';
				}
			}
		}
		for (int j = 0; j < (2 * m_size) * (6 * m_size); j++)
		{
			if (m_map[position].y - space == m_map[j].y && m_map[position].x == m_map[j].x)
			{
				if (m_map[j].ch == '#')
				{
					m_map[j].ch = ' ';
				}
			}
		}
		space++;
		if (space == 60)
			break;

	}
}