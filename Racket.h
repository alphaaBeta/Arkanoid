#pragma once

#include "Config.h"

/**
* \brief Class for racket.
*/
class Racket
{
private:
	Racket() : x(double((SCREEN_WIDTH)/2)), y(double(SCREEN_HEIGHT - BLOCK_HEIGHT*2)), speed(0.0), width(double(RACKET_LENGTH)) {}
	Racket(const Racket& org) : x(org.x), y(org.y), speed(org.speed), width(org.width) { }

public:
	

	static Racket& getInstance() {

		static Racket instance;
		return instance;
	}

	/////////////////////
	//----MAIN VARS----//
	/////////////////////


	/**
	* \brief Speed of the racket
	*/
	double speed;


	/**
	* \brief Width of the racket, from center.
	*/
	double width;
	

	/**
	* \brief X coordinate. Center of racket.
	*/
	double x;


	/**
	* \brief Y coordinate
	*/
	double y;


	/**
	* \brief Defining if shooting is possible
	*/
	char shootingEnabled;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	//
	/**
	* \brief Moves the racket, based on its speed.
	*
	* \param float timeStep
	*
	* \return 0 If border is hit.
	*/
	int Move(float);	

};

