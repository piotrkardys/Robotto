#include "Collision.h"
#pragma once
class Gears:public Collision
{
	vector<Sprite*> gears;
public:
	void loadGear();
	void addGear(Sprite *);
	void removeGear(Sprite*);
	void clearGears();
	vector<Sprite*> getGears();
	Gears();
	~Gears();
};

