#include"SFML\Audio.hpp"
#include<iostream>
#pragma once
using namespace sf;
class MusicPlayer
{
	Music music;
public:
	MusicPlayer();
	~MusicPlayer();
	void play();
	void setLoop(bool);
};

