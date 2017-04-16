#include "Ball.h"

#include <math.h>
#include "Racket.h"
#include "GameField.h"
#include "Block.h"

inline double GetDistanceFromLine(double x1, double x21, double x22 ) {	//check distance between coordinate (1) and a line (2) closest to it
	if (fabs(x1 - x21) > fabs(x1 - x22)) {
		return fabs(x1 - x22);
	}
	else return fabs(x1 - x21);
}


//initializing static vars
int Ball::BallAmmount = 0;


Ball *(Ball::BallArray)[BALL_LIMIT] = { 0 };

void Ball::MoveBalls() {
	for (int i = 0; i < BALL_LIMIT; i++) {
		BallArray[i]->Move();
	}
}


void Ball::MultiplyBalls(int amt, Ball& src) {

	if (amt > 0) {
		Ball aux(src);
		amt--;
		MultiplyBalls(amt, aux);
	}
}

char Ball::CheckCollision() {
	

	double xnew, ynew;
	xnew = this->x + Vx * ONE_STEP;
	ynew = this->y + Vy * ONE_STEP;
	char how;

	//checking collision with bordering walls
	if (GetDistanceFromLine(xnew, 0.0, double(FIELD_WIDTH))<=radius) {
		how = 'x';
		Bounce(how);

		return how;

	}
	if (GetDistanceFromLine(ynew, 0.0, double(FIELD_HEIGHT)) <= radius) {
		how = 'y';
		Bounce(how);

		return how;
	}

	//checking colllision with racket

	double RacketY = (Racket::getInstance()).y;
	double RacketX = (Racket::getInstance()).x;
	double RacketWidth = (Racket::getInstance()).width;

	if (GetDistanceFromLine(ynew, RacketY) <= radius) {
		if (GetDistanceFromLine(xnew, RacketX) <= RacketWidth/2) {
			how = 'p';
			Bounce(how);

			return how;
		}
	} 
	
	//checking collison with blocks
	
	if (signbit(this->Vx)) { xnew -= 1; }	//if Vx or Vy is negative, move the check range a bit
	if (signbit(this->Vy)) { ynew -= 1; }

	Block *aux = (GameField::getInstance()).BlockMatrix[int(round(ynew))][int(round(xnew))];
	if (aux==nullptr) {//let's check if nearest 'block' in matrix is filled
		if (GetDistanceFromLine(xnew, double(round(xnew))) <= radius) {
			how = 'x';
			Bounce(how, aux);

			return how;
		}
		else if (GetDistanceFromLine(ynew, double(round(ynew))) <= radius) {
			how = 'y';
			Bounce(how, aux);

			return how;
		}
	}
	return 0;

}

void Ball::Bounce(char how, Block *gothit) {
	
	double RSpeed;
	switch (how)
	{
	case 'p':	//TODO: improve this
		RSpeed = (Racket::getInstance()).speed; 
		if (signbit(Vx))
			this->Vx = Vx - RSpeed;
		else
			this->Vx = Vx + RSpeed;
		this->Vy = -Vy - RSpeed;

		break;

	case 'x':
		this->Vy = -Vy;

		if (gothit) {	//inform the block that we hit it
			(*gothit).Hit(this->power);
			gothit = 0;
		}
		break;

	case 'y':
		this->Vx = -Vx;

		if (gothit) {
			(*gothit).Hit(this->power);
			gothit = 0;
		}
		break;

	}

}

void Ball::Move(){

	char aux = this->CheckCollision();
	
	this->x = x + (Vx * ONE_STEP);
	this->y = y + (Vy * ONE_STEP);
	
}