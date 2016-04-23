#include "Highscores.h"

Score::Score() : name(""), score(0)
{
}

Score::~Score()
{
}

void Score::Add(string n, int s)
{
	name = n;
	score = s;
}

HighScores::HighScores()
{
	fstream plik;
	int i = 0;

	plik.open("data/Highscores.txt");

	while (!plik.eof() && i < 5){
		plik >> tab[i].name >> tab[i].score;
		i++;
	}

	plik.close();
}

HighScores::~HighScores()
{
}

void HighScores::Add(Score result)
{
	Score tmp;
	Score resulttmp(result);


	for (int i = 0; i < 5; i++){
		if (tab[i].score < resulttmp.score){
			tmp.name = tab[i].name;
			tmp.score = tab[i].score;
			tab[i].name = resulttmp.name;
			tab[i].score = resulttmp.score;
			resulttmp.name = tmp.name;
			resulttmp.score = tmp.score;
		}
		else if (tab[i].score == resulttmp.score){
			if ((tab[i].name > resulttmp.name) || (tab[i].name == "xxxx" && tab[i].name < resulttmp.name)){
				tmp.name = tab[i].name;
				tmp.score = tab[i].score;
				tab[i].name = resulttmp.name;
				tab[i].score = resulttmp.score;
				resulttmp.name = tmp.name;
				resulttmp.score = tmp.score;
			}
		}
	}
}


void HighScores::Save()
{
	fstream plik;

	plik.open("data/Highscores.txt");

	for (int i = 0; i < 5; i++)
		plik << tab[i].name << "\n" << tab[i].score << "\n";

	plik.close();
}
