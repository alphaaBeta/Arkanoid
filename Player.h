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

struct SaveData;

class FileOp
{
	friend Player;
protected:
	//Loads n level from JSON file
	static int LoadLevel(int n);

	//Loads a savefile
	static SaveData LoadGame();

	//Saves the game
	static int SaveGame(SaveData);
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
	int scoreAtStart, livesAtStart;

	/////////////////////

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	//Proceeds to next level
	int NextLevel(int);
	int LoadGame();
	int SaveGame();

	friend FileOp;
	

};




struct SaveData {
	int level, score, lives, difficulty;

	friend std::ostream& operator<<(std::ostream& os, const SaveData& obj) {
		os << obj.level << " " << obj.score << " " << obj.lives << " " << obj.difficulty;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, SaveData& obj)
	{
		//std::string level << is;
		//std::string score << is;
		//std::string lives << is;
		//std::string diff << is;
		istringstream iss;
		iss << is;

		obj.level << iss;
		obj.score << iss;
		obj.lives << iss;
		obj.difficulty << iss;


		return iss;
	}

	void LoadFromPlayer() {
		level = Player::getInstance().level;
		score = Player::getInstance().scoreAtStart;
		lives = Player::getInstance().livesAtStart;
		difficulty = Player::getInstance().difficulty;
	}
};


