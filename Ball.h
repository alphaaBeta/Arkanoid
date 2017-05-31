#pragma once

#include <vector>
#include "Config.h"


class Block;
class Racket;



class Ball
{

private:
	
	//Creates an independent ball
	Ball() {

		if (ballAmount == BALL_LIMIT - 1) { printf("Ball limit reached!"); }
		else {
			ballAmount++;


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

	static int ballAmount;
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

	//Sets new speed vectors for the ball
	//returns whether it bounced off the edge(block) or racket
	char Bounce(char, Block * = 0);

	//Calculates new ball location
	//returns whatever Bounce does
	char Move( float );

	//
	void Destroy();

	//Moves all the balls
	static char MoveBalls(float);

	//List to keep track of balls
	static std::vector<Ball *> ballList;

	
	static Ball* AddBall() { 
		Ball *newBall = new Ball;


		Ball::ballList.push_back(newBall);
		return newBall;
	}


	~Ball() { ballAmount--; }


};
