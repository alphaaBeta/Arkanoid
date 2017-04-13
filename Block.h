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
	int x, y; //for foremost left and down corner
	char resistance;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	void Bounce(Ball&);

	//TODO:
	//-map for different block types
	//-bonus drop?
};

