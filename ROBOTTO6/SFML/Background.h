#pragma once
#include"GameObject.h"
class Background :public GameObject
{
private:
	
	RectangleShape ground;
public:
	Background();
	~Background();
	void draw(RenderTarget&);
};


