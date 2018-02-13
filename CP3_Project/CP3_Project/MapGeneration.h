#pragma once
class MapGeneration
{
private:

	struct MapCoordinates
	{
		int x;
		int y;
		char ch;
		bool seen=false;
		bool moved = false;
	};
	int m_size;
	MapCoordinates *m_map;
	static int s_level;
	static int s_monsterCount;
	
public:
	MapGeneration(int size);
	~MapGeneration();
	void setSize(int size);
	void setMap(int size);
	void printMap(int placeInArray);
	void rePrintMap();
	void restartLevel();
	void bossLevel(int size);
	void clearMap();
	void showMap();
	void creatingDungeon(int position);
	friend class Interface;
	
};

