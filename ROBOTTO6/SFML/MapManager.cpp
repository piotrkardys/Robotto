#include "MapManager.h"

View camera(Vector2f(640, 360), Vector2f(1280, 720));
MapManager::MapManager(int lvl)
{
	char znak;
	std::ifstream plik;
	plik.open("data/level1.txt");

	camera.setCenter(Vector2f(640, 360));

	for (int i = 0; i < 23; i++){
		tiles[i].loadFromFile("data/level1.png", sf::IntRect(0, i * 64, 64, 64));
	}

	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++){
			plik >> znak;
			if ((znak - '\n') != 0)
				LEVEL[i][j] = znak - 'a';
			else{
				plik >> znak;
				LEVEL[i][j] = znak - 'a';
			}
		}
	}

	plik.close();
}

MapManager::~MapManager()
{

}

void MapManager::updateMap(Player player)
{
	int leftSide;
	int rightSide;

	leftSide = camera.getCenter().x / 64 - 10;
	if (leftSide < 0)
		leftSide = 0;

	rightSide = camera.getCenter().x / 64 + 10;
	if (rightSide > WIDTH)
		rightSide = WIDTH;

	for (int i = 0; i < HEIGHT; i++){
		for (int j = leftSide, x = 0; j < rightSide, x < windowWIDTH; j++, x++)
		{
			if (LEVEL[i][j] != 0 && LEVEL[i][j] != 19){
				vlevel[i][x].setTexture(tiles[LEVEL[i][j]]);
				vlevel[i][x].setPosition(j * 64, i * 64);
				obstacles.push_back(&vlevel[i][x]);
			}
			else if (LEVEL[i][j] != 0 && LEVEL[i][j] == 19 && !(player.getGlobalBounds().intersects(vlevel[i][x].getGlobalBounds()))){
				vlevel[i][x].setTexture(tiles[LEVEL[i][j]]);
				vlevel[i][x].setPosition(j * 64, i * 64);
			}
			else if (LEVEL[i][j] == 19 && (player.getGlobalBounds().intersects(vlevel[i][x].getGlobalBounds()))){
				++score;

				LEVEL[i][j] = 0;
			}
		}
	}
} 

void MapManager::drawMap(RenderWindow &window, Player *player)
{
	Texture *texture(&tiles[19]);
	for (int i = 0; i<HEIGHT; i++){
		for (int j = 0; j < windowWIDTH; j++)
			if (vlevel[i][j].getTexture() == texture && (player->getGlobalBounds().intersects(vlevel[i][j].getGlobalBounds()))){
				vlevel[i][j].setTexture(tiles[0]);
			}
			else{
				window.draw(vlevel[i][j]);
			}
	}
	obstacles.clear();
}

View MapManager::getCamera(){
	return camera;
}

void MapManager::moveCamera(Player player ,float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		if ((player.getPosition()).x >= 700 && (player.getPosition()).x <= 10800)
			camera.move(player.getVelocity().x * delta, 0);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		if ((player.getPosition()).x >= 700 && (player.getPosition()).x <= 10800)
			camera.move(player.getVelocity().x * delta, 0);
	}
}

vector <Sprite*> MapManager::getObstacles(){
	return obstacles;
}

int MapManager::getScore() {
	return score;
}