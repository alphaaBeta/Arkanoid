#pragma once

class Player	//singleton
{

private:
	Player() {}
	Player(const Player &);

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	int lives, score;
	char difficulty, level;

	/////////////////////


public:

	static Player& getInstance()
	{
		
		static Player instance;
		return instance;
	}
	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	void LoseLive();
	void AddPoints(int);
	void SetDifficulty(int);
	void SetLevel(int);
};
