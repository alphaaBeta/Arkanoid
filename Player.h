#pragma once

#include "Config.h"
#include "GameField.h"
#include "Ball.h"



#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "json.hpp"

class Enemy;

class Player;

struct SaveData;

/**
* \brief Class containing methods for operations between player and files.
*/
class FileOp
{
	friend Player;
protected:

	/**
	* \brief Loads a level from JSON file
	*
	* \param int Number of level to be loaded.
	*
	* \return int success flag.
	*/
	static int LoadLevel(int n);


	/**
	* \brief Loads a savefile
	*/
	static SaveData LoadGame();


	/**
	* \brief Saves the game to file.
	*/
	static int SaveGame(SaveData);
};




/**
* \brief Class containing all the data for player data: level, score, etc.
*/
class Player
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

	/**
	* \brief Lives the player has.
	*/
	int lives;
	
	
	/**
	* \brief Score a player has gained.
	*/
	int score;
	
	
	/**
	* \brief Number of current level.
	*/
	int level;
	
	
	/**
	* \brief Difficulty (not used)
	*/
	int difficulty;
	
	
	/**
	* \brief Score that player had at the start of the level. Score that is being saved.
	*/
	int scoreAtStart;
	
	
	/**
	* \brief Lives at the start of the level. Lives that are being saved.
	*/
	int livesAtStart;


	/////////////////////

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////


	/**
	* \brief Loads a certain level.
	*
	* \param int Number of level to be loaded.
	*
	* \return int Success flag.
	*/
	int LoadLevel(int);


	/**
	* \brief X
	*
	* \return int Success flag.
	*/
	int LoadGame();


	/**
	* \brief X
	*
	* \return int Success flag.
	*/
	int SaveGame();

	friend FileOp;
	

};



/**
* \brief A temporary struct to easen saving/loading procedure.
*/
struct SaveData {
	int level, score, lives, difficulty;

	friend std::ostream& operator<<(std::ostream& os, const SaveData& obj) {
		os << obj.level << " " << obj.score << " " << obj.lives << " " << obj.difficulty;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, SaveData& obj)
	{
		
		std::string level;
		is >> level;
		std::string	score;
		is >> score;
		std::string lives;
		is >> lives;
		std::string diff;
		is >> diff;

		is.clear();
		
		try {

			obj.level = std::stoi(level);
			obj.score = std::stoi(score);
			obj.lives = std::stoi(lives);
			obj.difficulty = std::stoi(diff);

		}
		catch (std::exception exc) {
			std::cerr << exc.what() << std::endl;
			obj.level = 1;
			obj.score = 0;
			obj.lives = 1;
			obj.difficulty = 1;
			return is;
		}

		return is;
	}

	void LoadFromPlayer() {
		level = Player::getInstance().level;
		score = Player::getInstance().scoreAtStart;
		lives = Player::getInstance().livesAtStart;
		difficulty = Player::getInstance().difficulty;
	}
};


