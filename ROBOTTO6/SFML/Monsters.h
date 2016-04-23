#include"Collision.h"
#include <algorithm>  
#pragma once
struct Monster {
	Sprite monsterSprite;
	int originPositionX;
	bool firstType;
};

class Monsters:public Collision
{
	vector<Monster> monsters;
	int maxLength = 100;
	int moveSpeed = 5;
	int actualLength = 0;
	bool right = true;
	int pointsForMonsters = 0;
	Vector2f startingPosition[8];

public:
	Monsters();
	~Monsters();

	void update(float, RenderWindow &,Sprite);
	void drawMonsters(RenderWindow &);
	void killMonster();
	int getPointsForMonsters();
	bool killPlayer(Sprite);
};
