#pragma once

#include "Config.h"
#include <vector>

class Block;
class Powerup;


class GameField	//singleton
{
public:


	/////////////////////
	//----MAIN VARS----//
	/////////////////////


	//Matrix to roughly know block location
	//Used to check if block is alredy placed in one place, to avoid multiple blocks on the same tile
	Block *blockMatrix[FIELD_WIDTH][FIELD_HEIGHT];

	//List to keep track of blocks
	static std::vector<Block *> blockList;

	//List to keep track of powerups
	static std::vector<Powerup *> powerupList;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	//TODO: void LoadBlockLayout();	//load specific block layout(from file)

	//x, y, type, colour
	int AddBlock(int, int, BlockType, Colour);	


	~GameField() {
		for (int i = 0; i < blockList.size(); i++) {
			delete (blockList[i]);//TODO??
		}
	}

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

