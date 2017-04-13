#pragma once

#include "GameField.h"
#include "Ball.h"


class Racket
{
public:
	Racket();
	~Racket();

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	int speed;
	double width;
	double x, y; //location of the center

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	void Bounce(Ball&);
	int Move();	//let's return 0 when hit the border


	//TODO:
	//-checks for bonuses player has

};

