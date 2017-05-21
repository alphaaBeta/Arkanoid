#pragma once

#include "Config.h"

class Player	//singleton
{

private:
	Player(): lives(3), score(0), level(1), difficulty(1) {}
	Player(const Player &) {}



public:

	static Player& getInstance()
	{
		
		static Player instance;
		return instance;

	}

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	int lives, score, level, difficulty;

	/////////////////////

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////


};
