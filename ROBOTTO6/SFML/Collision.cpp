#include "Collision.h" 


Collision::Collision()
{
}


Collision::~Collision()
{
}


bool Collision::checkIfCollision(vector<Sprite*> object_list){
	bool ifExists = false;
	for each(Sprite *adress in object_list){
		if (getGlobalBounds().intersects(adress->getGlobalBounds())){
			colidingObject = adress;
			ifExists = true;
			break;
		}
		else {
			ifExists = false;
		}
	}
	return ifExists;

}
bool Collision::checkIfCollisionTop(Sprite *object){

	if (object){
		if (getGlobalBounds().top > object->getGlobalBounds().top +gameTileCenterFix ) return true;
		else return false;
	}
	else{
		return false;
	}
}

bool Collision::checkIfCollisionBottom(Sprite * object){

	if (object){
		if (getGlobalBounds().top +getGlobalBounds().height  <= object->getGlobalBounds().top+gameTileCenterFix){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

bool Collision::checkIfCollisionLeft(Sprite * object){
	if (object){
		if (getGlobalBounds().left +getGlobalBounds().width <= object->getGlobalBounds().left +gameTileCenterFix) return true;
		else return false;
	}
	else{
		return false;
	}
}


bool Collision::checkIfCollisionRight(Sprite *object){
	if (object){
		if (getGlobalBounds().left > object->getGlobalBounds().left + gameTileCenterFix) return true;
		else return false;
	}
	else{
		return false;
	}
}


