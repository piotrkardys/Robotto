#pragma once
#include "GameObject.h"
class Collision :public GameObject
{
	Sprite *colidingObject;
public:
	Collision();
	~Collision();
	virtual bool checkIfCollision(vector<Sprite*>);
	virtual bool checkIfCollisionBottom(Sprite*);
	virtual bool checkIfCollisionTop(Sprite*);
	virtual bool checkIfCollisionLeft(Sprite*);
	virtual bool checkIfCollisionRight(Sprite*);
	Sprite *getColidingObject(){ return colidingObject; };
	
};


