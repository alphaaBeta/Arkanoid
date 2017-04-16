#pragma once


#include "Config.h"

class Block;
class Racket;


inline double GetDistanceFromLine(double, double, double = 999.0);

class Ball
{

private:
	

public:
	Ball() {

		BallAmmount++;

		this->x = double(FIELD_WIDTH) / 2;
		this->y = 2.0;
		this->Vx = 1.0;
		this->Vy = 1.0;

		//this->bncdOff = new Block;
		for (int i = 0; i < BALL_LIMIT; i++) {//TODO:...
			if (!BallArray[i]) {
				BallArray[i] = this;
				i = BALL_LIMIT;
			}
		}


	};

	Ball(Ball& src) {	//creates additional ball at former ball's location, with changed speed
		BallAmmount++;

		Ball();//????????????????????//

		this->x = src.x;
		this->y = src.y;
		this->Vx = src.Vx + 0.04 * src.Vx;
		this->Vy = src.Vy + 0.04 * src.Vy;

	}

	~Ball() {
		//delete bncdOff;
		//delete this;
	}



	static Ball *BallArray[BALL_LIMIT];


	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	static int BallAmmount;
	double radius;	//radius, 0.01 - one pixel
	double x, y, Vx, Vy;
	int power;
	//inline double V();	//inline for overall speed. useless?

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	void MultiplyBalls(int, Ball&);	//creates x balls at one's location recursively
	char CheckCollision();	//checks if ball will collide with an object or gamefield edge. 
							//Returns 'p' for racket, 'x' for horizontal and 'y' for vertical hit
	void Bounce(char, Block * = 0);
	void Move();

	static void MoveBalls();

	//TODO:
	//-checks for bonuses player has 
	//-something for ball limit

};

