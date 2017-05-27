#pragma once

#include "Config.h"
#include "GameField.h"
#include "Ball.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include "json.hpp"



class Player;

class FileOp
{
	friend Player;
protected:
	//Loads n level from JSON file
	static int LoadLevel(int n);

	//Loads a savefile
	//int LoadGame();

	//Saves the game
	//int SaveGame();
};

class Player	//singleton
{

private:
	Player(): lives(3), score(0), level(0), difficulty(1) {}
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

	//Proceeds to next level
	int NextLevel();
	int LoadGame();
	int SaveGame();

	friend FileOp;
	

};


