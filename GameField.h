#pragma once

#include "Block.h"

#define FIELD_WIDTH 16
#define FIELD_HEIGHT 20


class GameField
{
public:

	~GameField();

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	const int width, height;

	GameField() : width(FIELD_WIDTH), height(FIELD_HEIGHT) {
		Block *BlockMatrix[FIELD_HEIGHT][FIELD_WIDTH];	//creating a matrix to know block location
	};

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	void LoadBlockLayout();	//load specific block layout(from file)

private:
	
};

