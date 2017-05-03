#pragma once

#include "Config.h"

class Racket	//singleton
{
private:
	Racket() : x(double((SCREEN_WIDTH)/2)), y(double(SCREEN_HEIGHT - BLOCK_HEIGHT*2)), speed(0.0), width(double(RACKET_LENGTH)) {}
	Racket(const Racket& org) : x(org.x), y(org.y), speed(org.speed), width(org.width) { }

public:
	
	//~Racket();

	static Racket& getInstance() {

		static Racket instance;
		return instance;
	}

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	//Speed of the racket
	double speed;

	//Width of the racket
	double width;
	
	//location of the center
	double x, y; 

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	//Returns 0 if border is hit
	int Move(float);	


	//TODO:
	//-checks for bonuses player has

};

