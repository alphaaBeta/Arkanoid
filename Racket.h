#pragma once

#include "GameField.h"
#include "Ball.h"


class Racket	//singleton
{
private:
	Racket() {}
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

	int speed;
	double width;
	double x, y; //location of the center

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	int Move();	//let's return 0 when hit the border


	//TODO:
	//-checks for bonuses player has

};

