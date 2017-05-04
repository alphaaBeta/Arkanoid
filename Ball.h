#pragma once

#include <vector>

#include "Config.h"


class Block;
class Racket;


inline double GetDistanceFromLine(double, double, double = 999.0);

class Ball
{

private:
	
	//Creates an independent ball
	Ball() {

		if (BallAmount == BALL_LIMIT - 1) { printf("Ball limit reached!"); }
		else {
			BallAmount++;


			this->radius = 5;
			this->x = double(SCREEN_WIDTH) / 2;
			this->y = double(SCREEN_HEIGHT) / 2;
			this->Vx = 350;
			this->Vy = -350;
			this->power = 1;

		}

	}

	//creates additional ball at former ball's location
	Ball(Ball& src) {

		Ball *newBall = AddBall();

		newBall->x = src.x;
		newBall->y = src.y;
		newBall->Vx = src.Vx;
		newBall->Vy = src.Vy;
	}

public:



	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	static int BallAmount;
	int radius;
	double x, y, Vx, Vy;
	int power;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	//Creates x balls at one's location
	void MultiplyBalls(int, Ball&);	

	//checks if ball will collide with an object or gamefield edge. 
	//Returns 'p' for racket, 'x' for horizontal and 'y' for vertical hit
	char CheckCollision(float);

	char Bounce(char, Block * = 0);

	char Move( float );

	void Destroy();

	//Moves all the balls
	static char MoveBalls(float);

	//List to keep track of balls
	static std::vector<Ball *> BallList;

	
	static Ball* AddBall() { 
		Ball *newBall = new Ball;


		Ball::BallList.push_back(newBall);
		return newBall;
	}


	~Ball() {	}


};
