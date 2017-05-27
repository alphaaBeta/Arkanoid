#pragma once


#include "Config.h"
#include "GameField.h"
#include "Powerup.h"


class Block
{
public:
	Block(char hlt = 1, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255) : health(hlt), x(0), y(0) {
		colour.r = r;
		colour.g = g;
		colour.b = b;
		colour.a = a;
	}

	~Block() {}

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	Colour colour;

	//Cords for upper left corner
	int x, y; 

	//How many times a block can be hit before disappearing
	char health;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	void Hit(int = 1);	

	void Destroy();

};



class RegularBlock : public Block 
{
public:
	RegularBlock(char hlt = REGULAR_BLOCK_HEALTH, unsigned char r = 0, unsigned char g = 255, unsigned char b = 0, unsigned char a = 255)
		: Block(hlt, r, g, b, a) {}

};


class StrongBlock : public Block
{
public:
	StrongBlock(char hlt = STRONG_BLOCK_HEALTH, unsigned char r = 0, unsigned char g = 0, unsigned char b = 255, unsigned char a = 255)
		: Block(hlt, r, g, b, a) {}
};


class VeryStrongBlock : public Block
{
public:
	VeryStrongBlock(char hlt = VERY_STRONG_BLOCK_HEALTH, unsigned char r = 255, unsigned char g = 255, unsigned char b = 0, unsigned char a = 255)
		: Block(hlt, r, g, b, a) {}
};


class IndestructibleBlock : public Block
{
public:
	IndestructibleBlock(char hlt = INDESTRUCTIBLE_BLOCK_HEALTH, unsigned char r = 200, unsigned char g = 200, unsigned char b = 200, unsigned char a = 255)
		: Block(hlt, r, g, b, a) {}
};