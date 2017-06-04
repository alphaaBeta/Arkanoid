#pragma once

//#include <vector>

#include "Config.h"

#include "Ball.h"
#include "Player.h"
#include "Racket.h"
#include "GameField.h"
#include "Block.h"
//#include "Enemy.h"

class Powerup
{
public:
	Powerup(double xx, double yy) : x(xx), y(yy), Vy(POWERUP_SPEED) { }
	
	void Destroy() {
		for (int i = 0; i < GameField::getInstance().powerupList.size(); i++) {
			if ((GameField::getInstance()).powerupList[i] == this) {
				GameField::getInstance().powerupList.erase(GameField::getInstance().powerupList.begin() + i);
				delete this;
				
			}
		}
	}

	virtual void Collect() {}


	char Move(float timeStep) {
		double ynew = this->y + (Vy * timeStep);
		if (abs(this->y - Racket::getInstance().y) <= POWERUP_COLLECT_RANGE) {
			if (abs(this->x - Racket::getInstance().x) <= ((Racket::getInstance()).width / 2 + POWERUP_COLLECT_RANGE)) {
				this->Collect();
			}
		}
		if (ynew < SCREEN_HEIGHT) {
			this->y = ynew;
		}
		else if (ynew >= SCREEN_HEIGHT)
			return -1;	//returning information to be removed
		return 1;
	}

	static void MoveAll(float timeStep) {

		//If it falls out of the screen
		for (int i = 0; i < GameField::getInstance().powerupList.size(); i++) {
			if ((GameField::getInstance()).powerupList[i]->Move(timeStep) == -1) {
				//Remove
				(GameField::getInstance()).powerupList[i]->Destroy();
			}
		}
	}


	
	double x, y, Vy;

	Colour color;
};

class TripleBallPWUP : public Powerup {
public:
	void Collect() {

		Ball::ballList[0]->MultiplyBalls(TRIPLE_PWUP_BALL_NUMBER, *(Ball::ballList[0]));

		this->Destroy();
	}
	
	TripleBallPWUP(double xx, double yy) : Powerup(xx, yy) { this->color = { 0, 0, 255, 255 }; }
};

class BigBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < Ball::ballList.size(); i++) {
			Ball::ballList[i]->radius *= BIGBALL_PWUP_RADIUS_MULTIPLER;
		}
		this->Destroy();
	}

	BigBallPWUP(double xx, double yy) : Powerup(xx, yy) { this->color = { 0, 0, 255, 255 }; }
};

class ShootPWUP : public Powerup {
public:
	
	void Collect() {
		Racket::getInstance().shooting = 1;
		this->Destroy();
	}
	ShootPWUP(double xx, double yy) : Powerup(xx, yy) { this->color = { 255, 20, 147, 255 }; }
};

class ExtraLivePWUP : public Powerup {
public:
	void Collect() {
		(Player::getInstance()).lives += EXTRALIVE_PWUP_LIVE_AMT;
		this->Destroy();
	}
	ExtraLivePWUP(double xx, double yy) : Powerup(xx, yy) { this->color = { 0, 255, 0, 255 }; }
};

class BigRacketPWUP : public Powerup {
public:
	void Collect() {
		(Racket::getInstance()).width *= BIGRACKET_PWUP_INCRASE;
		this->Destroy();
	}
	BigRacketPWUP(double xx, double yy) : Powerup(xx, yy) { this->color = { 0, 255, 0, 255 }; }
};

class SmallRacketPWUP : public Powerup {
public:
	void Collect() {
		(Racket::getInstance()).width *= SMALLRACKET_PWUP_DECRASE;
		this->Destroy();
	}
	SmallRacketPWUP(double xx, double yy) : Powerup(xx, yy) { this->color = { 255, 0, 0, 255 }; }
};

class FastBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < Ball::ballList.size(); i++) {
			Ball::ballList[i]->Vx *= FASTBALL_PWUP_INCRASE;
			Ball::ballList[i]->Vy *= FASTBALL_PWUP_INCRASE;
		}
		this->Destroy();
	}
	FastBallPWUP(double xx, double yy) : Powerup(xx, yy) { this->color = { 255, 0, 0, 255 }; }
};

class SlowBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < Ball::ballList.size(); i++) {
			Ball::ballList[i]->Vx *= SLOWBALL_PWUP_DECRASE;
			Ball::ballList[i]->Vy *= SLOWBALL_PWUP_DECRASE;
		}
		this->Destroy();
	}
	SlowBallPWUP(double xx, double yy) : Powerup(xx, yy) { this->color = { 0, 255, 0, 255 }; }
};

