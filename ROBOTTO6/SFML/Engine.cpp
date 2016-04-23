#include "Engine.h"

Engine::Engine(sf::RenderWindow &win)
{
}


Engine::~Engine(void)
{
}
int Engine::runEngine(RenderWindow &window,Font font)
{

	bool menu = false;
	float t = 0;
	Clock clock;
	Player *player = new Player();
	Monsters *monsters = new Monsters;
	MapManager *map = new MapManager(1);
	Text score ("WYNIK: 0",font,40);
	score.setColor(Color(25,114,133));
	RectangleShape square;
	square.setSize(Vector2f(210, 64));
	square.setFillColor(Color::Black);
	while (!menu)
	{		
		cout <<"X: "<<player->getPosition().x << endl;
		cout <<"Y: "<<player->getPosition().y << endl;
			float delta = clock.getElapsedTime().asSeconds() - t;
			t = clock.getElapsedTime().asSeconds();

			map->moveCamera(*player,delta);
			window.setView(map->getCamera());


			map->updateMap(*player); 
			score.setPosition(map->getCamera().getCenter().x + 470, 7);
			square.setPosition(map->getCamera().getCenter().x + 435, 0);
			ostringstream ss;
			ss << map->getScore()+monsters->getPointsForMonsters();
			string wynik = ss.str();
			score.setString("WYNIK :" + wynik);


			player->update(delta, map->getObstacles(),window);
			monsters->update(delta, window,player->getSprite());


			window.clear(Color(181,181,181));
			

			monsters->drawMonsters(window);
			window.draw(*player);
			map->drawMap(window, player);
			window.draw(square);
			window.draw(score);
			window.display();


			if (player->getGlobalBounds().top > 850 || player->getGlobalBounds().left > 11000 || monsters->killPlayer(player->getSprite())){
				menu = true;
				delete(player);
				cout << "-----------------------------" << endl;
				delete(monsters);
				int a = map->getScore();
				delete(map);
				return a;
			}
	}
}
