#include "Obstacle.h"


Obstacle::Obstacle()
{
	loadFile("data/images/box.png");
	setAnimFrame(IntRect(0, 0, 96, 96));
	setPosition(Vector2f(1024 / 1.2, 200));
	setCenter(Vector2f(48, 48));

}


Obstacle::~Obstacle()
{
}
