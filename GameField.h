#pragma once

#include "Config.h"

class Block;

class GameField	//singleton
{
public:

	
	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	const int width, height;
	Block *BlockMatrix[FIELD_WIDTH][FIELD_HEIGHT]; //creating a matrix to roughly know block location
	

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	//TODO: void LoadBlockLayout();	//load specific block layout(from file)

	int AddBlock(int, int, BlockType, int);	//x, y, type, colour


	~GameField() {
		for (int i = 0; i < FIELD_WIDTH; i++) {	//removing matrix
			delete[] BlockMatrix[i];
		}
		delete[] BlockMatrix;
	}

	static GameField& getInstance()
	{

		static GameField instance;
		return instance;
	}


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

