#pragma once

#include "Config.h"
#include <vector>

class Block;
class Powerup;

/**
* \brief A class containing most elements needed to calculate behaviour.
*/
class GameField
{
public:


	/////////////////////
	//----MAIN VARS----//
	/////////////////////


	/**
	*Used to check if block is alredy placed in one place, to avoid multiple blocks on the same tile.
	*
	* \brief Matrix to roughly know block location
	*/
	Block *blockMatrix[FIELD_WIDTH][FIELD_HEIGHT];


	/**
	* \brief Vector to keep track of blocks
	*/
	static std::vector<Block *> blockList;


	/**
	* \brief Vector to keep track of powerups.
	*/
	static std::vector<Powerup *> powerupList;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////


	/**
	* \brief X
	*
	* \param X Y
	*
	* \return X Y
	*/
	int AddBlock(int, int, BlockType, Colour = { 0,0,0,0 });
	
	//Purge the matrix and vector
	void PurgeBlocks();

	//Checks if board is clear
	bool IsClear();


	~GameField();

	static GameField& getInstance()
	{

		static GameField instance;
		return instance;
	}


private:
	
	//Setting pointers to 0
	GameField() {
		for (int i = 0; i < FIELD_WIDTH; i++) {
			for (int j = 0; j < FIELD_HEIGHT; j++) {
				blockMatrix[i][j] = NULL;
			}
		}
	}


	GameField(const GameField&) {}

};

