#pragma once

#include <vector>
#include "Config.h"


class Block;
class Racket;


/**
* \brief A ball class. Contains all the methods that allow the ball to move, check collision etc.
*/
class Ball
{

private:

	/**
	* \brief Creates an independent ball
	*/
	Ball() {

		if (ballAmount == BALL_LIMIT - 1) { printf("Ball limit reached!"); }
		else {
			ballAmount++;


			this->radius = 5;
			this->x = double(SCREEN_WIDTH) / 2;
			this->y = double(SCREEN_HEIGHT - 50);
			this->Vx = 350;
			this->Vy = -350;
			this->power = 1;

		}

	}

	/**
	* \brief Creates additional ball at former ball's location
	*/
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
	/**
	* \brief Hold the current amount of balls.
	*/
	static int ballAmount;


	/**
	* Defines the ball radious, in pixels.
	* 
	* \brief Ball size.
	*/
	int radius;


	/**
	* \brief Ball x coordinate
	*/
	double x;
	/**
	* \brief Ball y coordinate
	*/
	double y;
	/**
	* \brief Ball horizontal speed
	*/
	double Vx;
	/**
	* \brief Ball vertical speed
	*/
	double Vy;


	/**
	* States how much "hitpoints" does every hit to a block take from it.
	* For example, power 3 destroys a block with 3 hitpoints in a single hit.
	*
	* \brief Defines how powerful the ball is.
	*/
	int power;

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////


	/**
	* \brief Creates int balls at Ball's location
	*
	* \param int Number of balls to be created
	*
	* \param Ball& Takes the Ball& location and speed to create those balls. Changes variables a bit.
	*/
	void MultiplyBalls(int, Ball&);	


	/**
	* \brief Checks if ball will collide with an object or gamefield edge. 
	*
	* \param float timeStep, to check future location
	*
	* \return 'p' for racket
	* \return 'x' for horizontal bounce
	* \return 'y' for vertical bounce
	*/
	char CheckCollision(float);


	/**
	* \brief Sets new speed vectors for a ball, after bouncing.
	*
	* \param char type of bounce
	* \param Block* Block that has been hit (if 0 - no block hit)
	*
	* \return 'p' for racket
	* \return 'x' for horizontal bounce
	* \return 'y' for vertical bounce
	*/
	char Bounce(char, Block * = 0);


	/**
	* \brief Calculates new ball location
	*
	* \param float timeStep, to check future location
	*
	* \return 'p' for racket
	* \return 'x' for horizontal bounce
	* \return 'y' for vertical bounce
	*/
	char Move( float );

	
	/**
	* \brief Moves all the balls on ballList vector
	*
	* \param float timeStep, for relaying to different Move(float) functions
	*
	* \return 'p' for racket
	* \return 'x' for horizontal bounce
	* \return 'y' for vertical bounce
	*/
	static char MoveBalls(float);


	/**
	* \brief Vector to keep track of balls.
	*/
	static std::vector<Ball *> ballList;

	
	/**
	* \brief Static method of adding one ball, accessing the constructor.
	*/
	static Ball* AddBall() { 
		Ball *newBall = new Ball;


		Ball::ballList.push_back(newBall);
		return newBall;
	}


	~Ball();


};
