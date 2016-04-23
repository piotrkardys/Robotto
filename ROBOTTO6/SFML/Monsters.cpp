#include "Monsters.h"


Monsters::Monsters()
{
	loadFile("data/images/monsters.png");
	setAnimFrame(IntRect(0, 0, 60, 46));
	setCenter(Vector2f(30, 24));

	startingPosition[0] = Vector2f(2390, 363);
	startingPosition[1] = Vector2f(3467, 231);
	startingPosition[2] = Vector2f(3432, 621);
	startingPosition[3] = Vector2f(4395, 487);
	startingPosition[4] = Vector2f(6152, 618);
	startingPosition[5] = Vector2f(8320, 360);
	startingPosition[6] = Vector2f(8984, 612);
	startingPosition[7] = Vector2f(10292, 618);

	Monster monster;

	for (int i = 0; i < 8; ++i){
		setPosition(startingPosition[i]);
		monster.monsterSprite = getSprite();
		monster.originPositionX = getPosition().x;
		monster.firstType = true;
		monsters.push_back(monster);
	}
	

}


Monsters::~Monsters()
{
}


void Monsters::update(float delta, RenderWindow &window , Sprite playa) {
	for (vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it){
		if (right == true){
			it->monsterSprite.move(Vector2f(moveSpeed, 0));
			if (it->originPositionX + maxLength == it->monsterSprite.getPosition().x){
				right = false;
			}
		}
		else {
			it->monsterSprite.move(Vector2f(-moveSpeed, 0));
			if (it->originPositionX - maxLength == it->monsterSprite.getPosition().x){
				right = true;
			}
		}
		if (it->monsterSprite.getGlobalBounds().intersects(playa.getGlobalBounds())){
			if (it->firstType){
				it->monsterSprite.setTextureRect(IntRect(60, 10, 68, 36));
			}
		}

	}
}


void Monsters::drawMonsters(RenderWindow &window) {
	for each (Monster monster in monsters) {
		window.draw(monster.monsterSprite);
	}
}

bool Monsters::killPlayer(Sprite player) {
	for (vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it){
		if (it->monsterSprite.getGlobalBounds().intersects(player.getGlobalBounds())){
			if (it->monsterSprite.getGlobalBounds().top <= player.getGlobalBounds().top + player.getGlobalBounds().height / 2){
				return true;
			}
			else {
				pointsForMonsters += 10;
				monsters.erase(it);
				return false;
			}
			break;
		}
	}
	return false;
}

int Monsters::getPointsForMonsters() {
	return pointsForMonsters;
}