#include "Game.h"

Game::Game(void)
{
	state = END;
	if (!font.loadFromFile("data/Digital_tech.otf"))
	{

		return;
	}
	window.create(VideoMode(1280, 720), "Robotto", Style::Close);
	window.setPosition(Vector2i(0, 0));
	state = MENU;
}


Game::~Game()
{
}
void Game::runGame()
{
	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::GAME:
			single();
			break;
		case GameState::HIGHSCORES:
			highScores();
			break;
		case GameState::GAME_OVER:
			endScreen();
			break;
		}
	}
}
void Game::menu()
{	
	View camera(Vector2f(640, 360), Vector2f(1280, 720));
	window.setView(camera);

	Texture textureMenu;
	textureMenu.loadFromFile("data/menu.png");
	Sprite pictureMenu;
	pictureMenu.setTexture(textureMenu);

	const int ile = 3;

	Text tekst[ile];

	string str[] = { "Play","Highscores", "Exit" };
	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition((1280 / 2 - tekst[i].getGlobalBounds().width / 2) + 100, 250 + i * 120);
	}

	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;


			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME;
			}
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = HIGHSCORES;
			}

			else if (tekst[2].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
			}
		}
		for (int i = 0; i < ile; i++){
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(Color::White);
			else tekst[i].setColor(Color::Black);

			window.clear(Color(181, 181, 181));

			window.draw(pictureMenu);
			for (int i = 0; i < ile; i++){
				window.draw(tekst[i]);
			}
			window.display();
		}
	}
}
void Game::single()
{
	View camera(Vector2f(640, 360), Vector2f(1280, 720));
	window.setView(camera);


	Engine *engine =  new Engine(window);
	MusicPlayer music;
	music.play();
	music.setLoop(true);
	score = engine->runEngine(window,font);
	delete(engine);
	state = GAME_OVER;
}

void Game::endScreen()
{	

	View camera(Vector2f(640, 360), Vector2f(1280, 720));
	window.setView(camera);

	Texture texture;
	texture.loadFromFile("data/highscores.png");
	Sprite picture;
	picture.setTexture(texture);

	Text title("KONIEC GRY", font, 100);
	title.setColor(Color::Black);
	title.setPosition((1280 / 2 - title.getGlobalBounds().width / 2) + 100, 40);

	Text button("PRZEJDZ DO TABELI", font, 80);
	button.setPosition((1280 / 2 - button.getGlobalBounds().width / 2) + 100, 500);

	const int ile = 3;

	Text tekst[ile];
	Text displayedName;
	displayedName.setFont(font);
	displayedName.setCharacterSize(80);
	displayedName.setColor(Color::Black);


	string name;
	ostringstream ss;
	ss << score;
	string wynik = ss.str();
	string str[] = { "TWOJ WYNIK", wynik , "WPISZ SWOJ NICK" };
	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(62);
		tekst[i].setColor(Color::Black);
		tekst[i].setString(str[i]);
		tekst[i].setPosition((1280 / 2 - tekst[i].getGlobalBounds().width / 2) + 100, 200 + i * 60);
	}

	while (state == GAME_OVER)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::TextEntered)
			{

				if (event.text.unicode < 128 && event.text.unicode != 8)
				{	
					name.push_back(event.text.unicode);
					displayedName.setString(name);
				}
				else if (event.text.unicode==8 && name.length() >0) {
					name.pop_back();
					displayedName.setString(name);
				}
			}else if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;

			else if (button.getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && name.length() != 0)
			{
				Score fullScore;
				fullScore.Add(name, score);
				HighScores highscores;
				highscores.Add(fullScore);
				highscores.Save();
				state = HIGHSCORES;
			}
		}
			if (button.getGlobalBounds().contains(mouse))
				button.setColor(Color::White);
			else button.setColor(Color::Black);

			displayedName.setPosition((1280 / 2 - displayedName.getGlobalBounds().width / 2) + 100, 400);
			window.clear(Color(181,181,181));
			window.draw(picture);
			window.draw(displayedName);
			window.draw(button);
			window.draw(title);
			for (int i = 0; i < ile; i++){
				window.draw(tekst[i]);
			}
			window.display();
		
	}
}

void Game::highScores(){
	View camera(Vector2f(640, 360), Vector2f(1280, 720));
	Vector2f mouse(Mouse::getPosition(window));
	window.setView(camera);
	Event event;

	Texture textureHS;
	textureHS.loadFromFile("data/highscores.png");
	Sprite pictureHS;
	pictureHS.setTexture(textureHS);

	HighScores highscores;
	Text title("HIGHSCORES", font, 80);
	Text button("PRZEJDZ DO MENU", font, 62);
	Text names[5];
	Text points[5];
	for (int i = 0; i < 5; ++i){
		names[i].setString(highscores.tab[i].name);
		names[i].setFont(font);
		names[i].setCharacterSize(28);
		names[i].setColor(Color::Black);
		names[i].setPosition((1280 / 2 - names[i].getGlobalBounds().width / 2) + 100, 170 + i * 75);
		ostringstream ss;
		ss << highscores.tab[i].score;
		string wynik = ss.str();
		points[i].setString(wynik);
		points[i].setFont(font);
		points[i].setCharacterSize(24);
		points[i].setColor(Color::Red);
		points[i].setPosition((1280 / 2 - points[i].getGlobalBounds().width / 2) + 100, 200 + i * 75);

	}



	title.setColor(Color::Black);
	button.setColor(Color::Black);
	button.setPosition((1280 / 2 - button.getGlobalBounds().width / 2) + 100, 550);
	title.setPosition((1280 / 2 - title.getGlobalBounds().width / 2) + 100, 70);

	while (window.pollEvent(event))
	{

		if (event.type == Event::Closed || event.type == Event::KeyPressed &&
			event.key.code == Keyboard::Escape)
			state = END;

		else if (button.getGlobalBounds().contains(mouse) &&
			event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
		{
			state = MENU;
		}
	}

	if (button.getGlobalBounds().contains(mouse))
		button.setColor(Color::White);
	else button.setColor(Color::Black);

	window.clear(Color(181, 181, 181));
	window.draw(pictureHS);
	window.draw(button);
	window.draw(title);
	for (int i = 0; i < 5; i++){
		window.draw(names[i]);
		window.draw(points[i]);
	}

	window.display();
}
