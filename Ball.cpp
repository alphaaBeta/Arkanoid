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

char Ball::MoveBalls(float timeStamp) {
	char how = 0;
	char aux = 0;
	for (int i = 0; i < Ball::BallList.size(); i++) {
		how  = (Ball::BallList[i])->Move(timeStamp);
		if (how != 0) { aux = how; }

	}
	return aux;
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

char Ball::CheckCollision( float timeStep) {
	





	double xnew, ynew;
	xnew = this->x + (this->Vx * timeStep);
	ynew = this->y + (this->Vy * timeStep);

	//Used to play sound
	char how;

	//Checking collison with blocks
	
	

	

	/*
	//Collision with blocks
	for (int i = 0; i < GameField::getInstance().BlockList.size(); i++) {
		double xc, xb = GameField::getInstance().BlockList[i]->x;
		double yc, yb = GameField::getInstance().BlockList[i]->y;

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

		//Get squared distance between the point and ball coord, check with ball radius(squared)
		if ((yc - this->y)*(yc - this->y) + (xc - this->x)*(xc - this->x) <= this->radius*this->radius) {

			//Check on which side of the block is it
			if(abs(yc-yb) <= 0.1 || abs(yc-yb-BLOCK_HEIGHT) <= 0.1)
			 how = Bounce('y', GameField::getInstance().BlockList[i]);
			else how = Bounce('x', GameField::getInstance().BlockList[i]);
			return how;
		}
		
	}*/
	int xCord, yCord;
	
	if (Vy < 0) {
		xCord = int(xnew/BLOCK_WIDTH);
		yCord = round((ynew - radius)/BLOCK_HEIGHT) - 1;
		if (xCord < 0 || yCord < 0 || xCord >= FIELD_WIDTH || yCord >= FIELD_HEIGHT) {}

		else if (GameField::getInstance().BlockMatrix[xCord][yCord]) {
			how = Bounce('y', GameField::getInstance().BlockMatrix[xCord][yCord]);
			return how;
		}
	}else {
		xCord = int(xnew / BLOCK_WIDTH);
		yCord = round((ynew + radius) / BLOCK_HEIGHT);
		if (xCord < 0 || yCord < 0 || xCord >= FIELD_WIDTH || yCord >= FIELD_HEIGHT) {}

		else if (GameField::getInstance().BlockMatrix[xCord][yCord]) {
			how = Bounce('y', GameField::getInstance().BlockMatrix[xCord][yCord]);
			return how;
		}
	}

	if (Vx < 0) {
		xCord = round((xnew - radius) / BLOCK_WIDTH) - 1;
		yCord = int(ynew / BLOCK_HEIGHT);
		if (xCord < 0 || yCord < 0 || xCord >= FIELD_WIDTH || yCord >= FIELD_HEIGHT) {}

		else if(GameField::getInstance().BlockMatrix[xCord][yCord]) {
			how = Bounce('x', GameField::getInstance().BlockMatrix[xCord][yCord]);
			return how;
		}
	}else {
		xCord = round((xnew + radius) / BLOCK_WIDTH);
		yCord = int(ynew / BLOCK_HEIGHT);
		if (xCord < 0 || yCord < 0 || xCord >= FIELD_WIDTH || yCord >= FIELD_HEIGHT) {}

		else if (GameField::getInstance().BlockMatrix[xCord][yCord]) {
			how = Bounce('x', GameField::getInstance().BlockMatrix[xCord][yCord]);
			return how;
		}
	}
	

	//checking colllision with racket

	double RacketY = (Racket::getInstance()).y;
	double RacketX = (Racket::getInstance()).x;
	double RacketWidth = (Racket::getInstance()).width;

	if (abs(ynew - RacketY) <= this->radius) {
		if (RacketX - RacketWidth/2 <= xnew && RacketX + RacketWidth/2 >= xnew) {
			how = 'p';
			how = Bounce(how);

			return how;
		}
	}

	//checking collision with bordering walls
	if ((xnew <= radius) || ((SCREEN_WIDTH - xnew) <= radius)) {
		how = 'x';
		how = Bounce(how);

		return how;

	}
	if ((ynew <= radius)) {
		how = 'y';
		how = Bounce(how);

		return how;
	}

	//if it falls out of the screen
	if (ynew > SCREEN_HEIGHT) {
		this->Destroy();

		if (Ball::BallList.empty()) {
			Player::getInstance().lives--;
			if ((Player::getInstance()).lives)
				AddBall();
		}
		Ball::BallAmount--;
	}

	
	return 0 ;

}

void Ball::Destroy() {
	for (int i = 0; i < Ball::BallList.size(); i++) {
		if (Ball::BallList[i] == this) {

			delete Ball::BallList[i];

			Ball::BallList.erase(Ball::BallList.begin() + i);
			
		}
	}
}

char Ball::Bounce(char how, Block *gothit) {
	
	double inter, angle, ballSpeed;
	switch (how)
	{

	case 'p':

		//Calculating the speed of the ball after bouncing off the paddle

		inter = Racket::getInstance().x - this->x;
		inter = inter / (Racket::getInstance().width / 2);

		//Maximum angle of the bounce
		angle = inter * 5 * PI / 12; //75 degrees

		//sum of x and y speed vectors
		ballSpeed = sqrt(Vx*Vx + Vy*Vy);

		this->Vx = -ballSpeed*sin(angle);
		this->Vy = -ballSpeed*cos(angle);
		
		return 'p';

	case 'x':
		this->Vx = -Vx;

		if (gothit) {	
			//Inform the block that we hit it
			(*gothit).Hit(this->power);
			gothit = 0;
		}
		
		return 'x';

	case 'y':
		this->Vy = -Vy;


		if (gothit) {
			(*gothit).Hit(this->power);
			gothit = 0;
		}
		
		return 'x';

	}
	return 0;

}

char Ball::Move( float timeStep){

	char aux = (this->CheckCollision)(timeStep);
	
	this->x += (Vx * timeStep);
	this->y += (Vy * timeStep);
	return aux;
	
}