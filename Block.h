#pragma once


#include "Config.h"
#include "GameField.h"
#include "Powerup.h"

/**
* \brief A class for a block
*/
class Block
{
public:
	Block(char hlt = 1, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255) : health(hlt), x(0), y(0) {
		colour.r = r;
		colour.g = g;
		colour.b = b;
		colour.a = a;
	}

	~Block();

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	/**
	* Block colour, defined by struct in Config.h. Contains of red, green, blue and alpha values, ranging from 0-255.
	*
	* \brief Block colour.
	*/
	Colour colour;


	/**
	* \brief x coordinate of upper left corner.
	*/
	int x;
	/**
	* \brief y coordinate of upper left corner
	*/
	int y; 


	/**
	* Defines how many times a block can be hit before disappearing.
	*
	* \brief Block "hitpoints"
	*/
	char health;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////


	/**
	* \brief Records a block being hit, performs appropriate actions.
	*
	* \param int Strength of a hit (power)
	*/
	void Hit(int = 1);	


};


/**
* \brief Regular block with health = REGULAR_BLOCK_HEALTH (config.h)
*/
class RegularBlock : public Block 
{
public:
	RegularBlock(char hlt = REGULAR_BLOCK_HEALTH, unsigned char r = 0, unsigned char g = 255, unsigned char b = 0, unsigned char a = 255)
		: Block(hlt, r, g, b, a) {}

};

/**
* \brief Stronger block with health = STRONG_BLOCK_HEALTH (config.h)
*/
class StrongBlock : public Block
{
public:
	StrongBlock(char hlt = STRONG_BLOCK_HEALTH, unsigned char r = 0, unsigned char g = 0, unsigned char b = 255, unsigned char a = 255)
		: Block(hlt, r, g, b, a) {}
};

/**
* \brief Even stronger block with health = VERY_STRONG_BLOCK_HEALTH (config.h)
*/
class VeryStrongBlock : public Block
{
public:
	VeryStrongBlock(char hlt = VERY_STRONG_BLOCK_HEALTH, unsigned char r = 255, unsigned char g = 255, unsigned char b = 0, unsigned char a = 255)
		: Block(hlt, r, g, b, a) {}
};


/**
* \brief Block that cannot be destroyed
*/
class IndestructibleBlock : public Block
{
public:
	IndestructibleBlock(char hlt = INDESTRUCTIBLE_BLOCK_HEALTH, unsigned char r = 200, unsigned char g = 200, unsigned char b = 200, unsigned char a = 255)
		: Block(hlt, r, g, b, a) {}
};