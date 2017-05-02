#include "Ball.h"

#include <math.h>
#include <vector>
#include "Racket.h"
#include "GameField.h"
#include "Block.h"

#define PI 3.14159265


//initializing static vars

//Amount of balls
int Ball::BallAmount = 0;


std::vector<Ball *> Ball::BallList;

void Ball::MoveBalls(float timeStamp) {
	for (int i = 0; i < Ball::BallList.size(); i++) {
		Ball::BallList[i]->Move(timeStamp);
	}
}


void Ball::MultiplyBalls(int amt, Ball& src) {

	if (amt > 0) {
		Ball *aux = AddBall();

		aux->x = src.x;
		aux->y = src.y;
		aux->Vx = src.Vx + src.Vx*0.02;
		aux->Vy = src.Vy + src.Vy*0.02;

		amt--;
		MultiplyBalls(amt, *aux);
	}
}

void Ball::CheckCollision( float timeStep) {
	





	double xnew, ynew;
	xnew = this->x + (this->Vx * timeStep);
	ynew = this->y + (this->Vy * timeStep);
	char how;

	//Checking collison with blocks
	
	

	

	
	//Collision with blocks
	for (int i = 0; i < GameField::getInstance().BlockList.size(); i++) {
		int xc, xb = GameField::getInstance().BlockList[i]->x;
		int yc, yb = GameField::getInstance().BlockList[i]->y;

		//Find closest x coord on the block, according to ball
		if (this->x < xb) {
			xc = xb;
		}
		else if (this->x > xb + BLOCK_WIDTH) {
			xc = xb + BLOCK_WIDTH;
		}
		else
			xc = this->x;


		//Find closest y coord on the block, according to ball
		if (this->y < yb) {
			yc = yb;
		}
		else if (this->y > yb + BLOCK_HEIGHT) {
			yc = yb + BLOCK_HEIGHT;
		}
		else
			yc = this->y;

		//Get squared distance between the point and ball coord, check with ball radius - squared
		if ((yc - this->y)*(yc - this->y) + (xc - this->x)*(xc - this->x) <= this->radius*this->radius) {

			//Check on which side of the block is it
			if(abs(yc-yb) <= 0.01 || abs(yc-yb-BLOCK_HEIGHT) <= 0.01)
			Bounce('y', GameField::getInstance().BlockList[i]);
			else Bounce('x', GameField::getInstance().BlockList[i]);
		}
	}


	

	//checking colllision with racket

	double RacketY = (Racket::getInstance()).y;
	double RacketX = (Racket::getInstance()).x;
	double RacketWidth = (Racket::getInstance()).width;

	if (abs(ynew - RacketY) <= this->radius) {
		if (RacketX - RacketWidth/2 <= xnew && RacketX + RacketWidth/2 >= xnew) {
			how = 'p';
			Bounce(how);

			return;
		}
	}

	//checking collision with bordering walls
	if ((xnew <= radius) || ((SCREEN_WIDTH - xnew) <= radius)) {
		how = 'x';
		Bounce(how);

		return;

	}
	if ((ynew <= radius) || ((SCREEN_HEIGHT - ynew) <= radius)) {
		how = 'y';
		Bounce(how);

		return;
	}

	
	return;

}

void Ball::Bounce(char how, Block *gothit) {
	
	double RSpeed;
	double xSpeed;
	double ratio;
	double RacketX = (Racket::getInstance()).x;
	double RacketWidth = (Racket::getInstance()).width;
	double inter, angle, ballSpeed;
	switch (how)
	{
	case 'p':



		inter = RacketX - this->x;
		inter = inter / (RacketWidth / 2);
		angle = inter * 5 * PI / 12;//75 degrees

		ballSpeed = sqrt(Vx*Vx + Vy*Vy);	//sum of x and y speed vectors

		this->Vx = -ballSpeed*sin(angle);
		this->Vy = -ballSpeed*cos(angle);

		break;

	case 'x':
		this->Vx = -Vx;

		if (gothit) {	
			//Inform the block that we hit it
			(*gothit).Hit(this->power);
			gothit = 0;
		}
		break;

	case 'y':
		this->Vy = -Vy;


		if (gothit) {
			(*gothit).Hit(this->power);
			gothit = 0;
		}
		break;

	}

}

void Ball::Move( float timeStep){

	//char aux = 
		this->CheckCollision(timeStep);
	
	this->x += (Vx * timeStep);
	this->y += (Vy * timeStep);
	
}