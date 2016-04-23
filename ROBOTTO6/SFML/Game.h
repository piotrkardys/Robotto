#pragma once
#include "Engine.h"
#include"HighScores.h"
#include "MusicPlayer.h"
#include<Windows.h>
#include<string>

using namespace std;
using namespace sf;
class Game
{
public:
	Game(void);
	~Game(void);

	void runGame();
	void single();
	void endScreen();
	void highScores();
	string chooseName();
	enum GameState { MENU, GAME, GAME_OVER, END, HIGHSCORES };
	GameState state;

private:
	Font font;
	RenderWindow window;
	void menu();
	int score = 0;
};

