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
	* \brief Adds a block to the matrix - gamefield.
	*
	* \param int X coordinate in matrix
	* \param int Y coordinate in matrix
	* \param BlockType BlockType of the block to be placed
	* \param Colour Colour of the block to be palced
	*
	* \return 1 If placed successfully
	* \return 0 If block exists in that spot
	*/
	int AddBlock(int, int, BlockType, Colour = { 0,0,0,0 });
	

	/**
	* \brief Purge the matrix and vector
	*/
	void PurgeBlocks();


	/**
	* \brief Checks if board is clear
	*/
	bool IsClear();


	~GameField();

	static GameField& getInstance()
	{

		static GameField instance;
		return instance;
	}


private:
	

	/**
	* \brief Sets all pointers to 0
	*/
	GameField() {
		for (int i = 0; i < FIELD_WIDTH; i++) {
			for (int j = 0; j < FIELD_HEIGHT; j++) {
				blockMatrix[i][j] = NULL;
			}
		}
	}


	GameField(const GameField&) {}

};

