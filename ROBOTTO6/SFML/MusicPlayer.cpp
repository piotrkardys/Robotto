#include "MusicPlayer.h"


MusicPlayer::MusicPlayer()
{
	if (!music.openFromFile("data/robotto.wav")){
		std::cout << "Nie dziala" << std::endl;
		return;
	}
}


MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::play(){
	music.play();
}

void MusicPlayer::setLoop(bool temp){
	music.setLoop(temp);
}