#pragma once

#include "Block.h"

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 16


class GameField	//singleton
{
public:

	~GameField();

	static GameField& getInstance()
	{

		static GameField instance;
		return instance;
	}

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	const int width, height;
	Block *BlockMatrix[FIELD_HEIGHT][FIELD_WIDTH]; //creating a matrix to roughly know block location
	

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	void LoadBlockLayout();	//load specific block layout(from file)
	int AddBlock();

private:
	
	GameField() : width(FIELD_WIDTH), height(FIELD_HEIGHT) {
		for (int i = 0; i < FIELD_WIDTH; i++) {	//setting pointers to 0
			for (int j = 0; j < FIELD_HEIGHT; j++) {
				BlockMatrix[i][j] = nullptr;
			}
		}
	}

	GameField(const GameField&);

};

