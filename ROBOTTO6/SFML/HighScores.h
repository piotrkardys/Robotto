#include <string>
#include <fstream>

using namespace std;

struct Score{
	string name;
	int score;

	Score();
	~Score();
	void Add(string, int);
};

class HighScores{
public:	

	Score tab[5];
	HighScores();
	~HighScores();
	void Add(Score);
	void Save();
};
