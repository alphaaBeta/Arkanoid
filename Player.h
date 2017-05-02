#pragma once

#include "Config.h"

class Player	//singleton
{

private:
	Player(): lives(3), score(0), difficulty(1), level(1) {}
	Player(const Player &);



public:

	static Player& getInstance()
	{
		
		static Player instance;
		return instance;

	}

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	int lives, score;
	char difficulty, level;

	/////////////////////

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	

};
