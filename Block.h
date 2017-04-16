#pragma once

#include "Config.h"




class Block
{
public:
	Block(char hlt = 1, int clr = 0, char sX = 2, char sY = 1) : health(hlt), colour(clr), sizeX(sX), sizeY(sY) { }
	~Block() { delete this; }

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	int colour;
	int x1, y1; //for lower left corner
	char sizeX, sizeY;	//width and height. 1 means it takes up one space in matrix
	char health;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	void Hit(int);	//argument for strength
	void Destroy();

	//TODO:
	//-bonus drop chance on Destroy
};



class RegularBlock : public Block 
{
public:
	RegularBlock(char hlt = REGULAR_BLOCK_HEALTH, int clr = 0) : Block(hlt, clr) {}
};


class StrongBlock : public Block
{
public:
	StrongBlock(char hlt = STRONG_BLOCK_HEALTH, int clr = 2) : Block(hlt, clr) {}
};


class VeryStrongBlock : public Block
{
public:
	VeryStrongBlock(char hlt = VERY_STRONG_BLOCK_HEALTH, int clr = 4) : Block(hlt, clr) {}
};


class IndestructibleBlock : public Block
{
public:
	IndestructibleBlock(char hlt = INDESTRUCTIBLE_BLOCK_HEALTH, int clr = 6) : Block(hlt, clr) {}
};