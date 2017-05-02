#pragma once

#include "Config.h"
#include <vector>

class Block;


class GameField	//singleton
{
public:


	/////////////////////
	//----MAIN VARS----//
	/////////////////////


	//Matrix to roughly know block location
	Block *BlockMatrix[FIELD_WIDTH][FIELD_HEIGHT];
	static std::vector<Block *> BlockList;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	//TODO: void LoadBlockLayout();	//load specific block layout(from file)

	int AddBlock(int, int, BlockType, Colour);	//x, y, type, colour


	~GameField() {
		/*for (int i = 0; i < FIELD_WIDTH; i++) {	//removing matrix
			delete[] BlockMatrix[i];
		}
		delete[] BlockMatrix;*/
		for (int i = 0; i < BlockList.size(); i++) {
			delete BlockList[i];
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
				BlockMatrix[i][j] = NULL;
			}
		}
	}

	GameField(const GameField&) {

	}

};

