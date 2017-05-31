#include "Ball.h"

#include <math.h>
#include <vector>
#include "Racket.h"
#include "GameField.h"
#include "Block.h"
#include "Enemy.h"

#define PI 3.14159265


//initializing static vars

//Amount of balls
int Ball::ballAmount = 0;


std::vector<Ball *> Ball::ballList;

char Ball::MoveBalls(float timeStamp) {
	char how = 0;
	char aux = 0;
	for (int i = 0; i < Ball::ballList.size(); i++) {
		how  = (Ball::ballList[i])->Move(timeStamp);
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


Ball::~Ball() {
	for (int i = 0; i < Ball::ballList.size(); i++) {
		if (Ball::ballList[i] == this) {
			Ball::ballList.erase(Ball::ballList.begin() + i);
			ballAmount--;
		}
	}
}

char Ball::CheckCollision( float timeStep) {
	





	double xnew, ynew;
	xnew = this->x + (this->Vx * timeStep);
	ynew = this->y + (this->Vy * timeStep);

	//Used to play sound
	char how;

	//Checking collison with blocks
	int xCord, yCord;
	
	if (Vy < 0) {
		xCord = int(xnew/BLOCK_WIDTH);
		yCord = int(round((ynew - radius)/BLOCK_HEIGHT)) - 1;
		if (xCord < 0 || yCord < 0 || xCord >= FIELD_WIDTH || yCord >= FIELD_HEIGHT) {}

		else if (GameField::getInstance().blockMatrix[xCord][yCord]) {
			how = Bounce('y', GameField::getInstance().blockMatrix[xCord][yCord]);
			return how;
		}
	}else {
		xCord = int(xnew / BLOCK_WIDTH);
		yCord = int(round((ynew + radius) / BLOCK_HEIGHT));
		if (xCord < 0 || yCord < 0 || xCord >= FIELD_WIDTH || yCord >= FIELD_HEIGHT) {}

		else if (GameField::getInstance().blockMatrix[xCord][yCord]) {
			how = Bounce('y', GameField::getInstance().blockMatrix[xCord][yCord]);
			return how;
		}
	}

	if (Vx < 0) {
		xCord = int(round((xnew - radius) / BLOCK_WIDTH)) - 1;
		yCord = int(ynew / BLOCK_HEIGHT);
		if (xCord < 0 || yCord < 0 || xCord >= FIELD_WIDTH || yCord >= FIELD_HEIGHT) {}

		else if(GameField::getInstance().blockMatrix[xCord][yCord]) {
			how = Bounce('x', GameField::getInstance().blockMatrix[xCord][yCord]);
			return how;
		}
	}else {
		xCord = int(round((xnew + radius) / BLOCK_WIDTH));
		yCord = int(ynew / BLOCK_HEIGHT);
		if (xCord < 0 || yCord < 0 || xCord >= FIELD_WIDTH || yCord >= FIELD_HEIGHT) {}

		else if (GameField::getInstance().blockMatrix[xCord][yCord]) {
			how = Bounce('x', GameField::getInstance().blockMatrix[xCord][yCord]);
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
		delete this;

		if (Ball::ballList.empty()) {
			Player::getInstance().lives--;
			if ((Player::getInstance()).lives)
				AddBall();
		}
		Ball::ballAmount--;
	}

	//Checking collision with enemies
	for (int i = 0; i < Enemy::enemyList.size(); i++) {
		Enemy * aux = Enemy::enemyList[i];
		double distance = (xnew - aux->x)*(xnew - aux->x) + (ynew - aux->y)*(ynew - aux->y);

		if (distance < ENEMY_SIZE*ENEMY_SIZE) {
			how = 'y';
			how = Bounce(how);
			delete aux;


			return how;
		}
		

	}

	
	return 0 ;

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