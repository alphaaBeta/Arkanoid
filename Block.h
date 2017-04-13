#pragma once

#include "Ball.h"


class Block
{
public:
	Block();
	~Block();

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	int colour;
	int x1, y1; //for lower left corner
	int x2 = x1 + 2;	//size is the same for all blocks
	int y2 = y1 + 2;
	//int x2, y2;	//for upper right corner
	char resistance;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	void Hit(int);

	//TODO:
	//-map for different block types
	//-bonus drop?
};

