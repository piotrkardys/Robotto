#include "Background.h"


Background::Background()
{	

	ground.setPosition(Vector2f(0, 352));
	ground.setSize(Vector2f(1024, 212));
	ground.setFillColor(Color::Red);
}


Background::~Background()
{
}

void Background::draw(RenderTarget & target){
	target.draw(ground);
}