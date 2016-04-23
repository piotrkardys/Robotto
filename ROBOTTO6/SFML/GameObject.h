#pragma once
#include <SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include<iostream>
#include <sstream>
static const float gravity = 15;
static const int groundHeight = 1000;
//static float counter = 0;
static const int gameTileCenterFix = 32;




using namespace sf;
using namespace std;
class GameObject :public Drawable
{
private:
	 Texture texture;
	 Sprite sprite;

public:
	GameObject();
	~GameObject();
	virtual bool loadFile(String);
	virtual void loadFromTexture(Texture);
	virtual void setAnimFrame(IntRect&);
	virtual void setPosition(Vector2f);
	virtual Vector2f getPosition();
	virtual FloatRect getSize();
	virtual void setCenter(Vector2f);
	virtual Vector2f getCenter();
	virtual void draw(RenderTarget&,RenderStates) const;
	virtual void move(Vector2f);
	virtual FloatRect getGlobalBounds();
	virtual Sprite getSprite();

};

