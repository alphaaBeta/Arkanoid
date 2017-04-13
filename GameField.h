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

private:
	
	GameField() : width(FIELD_WIDTH), height(FIELD_HEIGHT) {}

	GameField(const GameField&);

};

