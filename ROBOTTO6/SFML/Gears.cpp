#include "Gears.h"


Gears::Gears()
{
}


Gears::~Gears()
{
}

void Gears::addGear(Sprite *object){
	gears.push_back(object);
}

void Gears::removeGear(Sprite *object){
}
void Gears::clearGears(){
	gears.clear();
}

vector<Sprite*> Gears::getGears(){
	return gears;
}