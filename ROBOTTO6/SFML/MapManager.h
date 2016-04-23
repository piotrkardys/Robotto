#include "Player.h"
#include "Obstacle.h"
#include "Monsters.h"
#include "Gears.h"
#include <fstream>
#pragma once
const int WIDTH = 180;
const int HEIGHT = 12;
const int windowWIDTH = 25;

class MapManager{
private:
	int score = 0;
	short LEVEL[HEIGHT][WIDTH];
	Texture tiles[23];	
	Sprite	vlevel[12][30];
	vector<Sprite*> obstacles;
	Gears gears;

public:
	MapManager(int);
	~MapManager();
	void updateMap(Player);
	View getCamera();
	void drawMap(RenderWindow &,Player *);
	void moveCamera(Player,float);
	int getScore();
	vector <Sprite*> getObstacles();
};
