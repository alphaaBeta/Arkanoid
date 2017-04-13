#include "Ball.h"
#include "Racket.h"
#include "GameField.h"

#include <math.h>

inline double CheckDistance(double x1, double x21 , double x22 = 999.0) {	//check distance between coordinate (1) and a line (2) closest to it
	if (abs(x1 - x21) > abs(x1 - x22)) {
		return abs(x1 - x22);
	}
	else return abs(x1 - x21);
}


inline double Ball::V() {
	return (sqrt((Vx*Vx) + (Vy*Vy)));
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
	xnew = this->x + Vx * 0.01;
	ynew = this->y + Vy * 0.01;
	//checking collision with bordering walls
	if (CheckDistance(xnew, 0.0, double(FIELD_WIDTH))<=radius) {
		return 'x';
	}
	if (CheckDistance(ynew, 0.0, double(FIELD_HEIGHT)) <= radius) {
		return 'y';
	}

	//checking colllision with racket
	double RacketY = (Racket::getInstance()).y;
	double RacketX = (Racket::getInstance()).x;
	double RacketWidth = (Racket::getInstance()).width;

	if (CheckDistance(ynew, RacketY) <= radius) {
		if (CheckDistance(xnew, RacketX) <= RacketWidth/2) {
			return 'p';
		}
	} 
	
	Block *aux = (GameField::getInstance()).BlockMatrix[int(round(ynew))][int(round(xnew))];
	if (aux==nullptr) {//let's check if nearest 'block' in matrix is filled
		if (CheckDistance(xnew, double(round(xnew))) <= radius) {
			bncdOff = aux;
			return 'x';
		}
		else if (CheckDistance(ynew, double(round(ynew))) <= radius) {
			bncdOff = aux;
			return 'y';
		}
	}

}

void Ball::Bounce(char how, Block *gothit = 0) {
	
	
	switch (how)
	{
	case 'p':	//TODO: improve this
		double RSpeed = (Racket::getInstance()).speed; //?????????????????//
		if (signbit(Vx))
			this->Vx = Vx - RSpeed;
		else
			this->Vx = Vx + RSpeed;
		this->Vy = -Vy - RSpeed;

		break;

	case 'x':
		this->Vy = -Vy;

		if (gothit) {	//inform the block that we hit it
			(*gothit).Hit();
			gothit = 0;
			bncdOff = 0;
		}
		break;

	case 'y':
		this->Vx = -Vx;

		if (gothit) {
			(*gothit).Hit();
			gothit = 0;
			bncdOff = 0;
		}
		break;

	}

}