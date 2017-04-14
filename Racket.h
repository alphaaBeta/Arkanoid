#pragma once

#include "GameField.h"
#include "Ball.h"


class Racket	//singleton
{
private:
	Racket() : x(FIELD_WIDTH/2), y(1), speed(0.02), width(2.0) {}
	Racket(const Racket&);

public:
	
	~Racket();

	static Racket& getInstance() {

		static Racket instance;
		return instance;
	}

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	double speed;
	double width;
	double x, y; //location of the center

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	int Move(char, double);	//let's return 0 when hit the border


	//TODO:
	//-checks for bonuses player has

};

