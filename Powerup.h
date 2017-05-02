#pragma once

#include "Config.h"

#include "Ball.h"
#include "Player.h"
#include "Racket.h"
#include "GameField.h"


class Powerup
{
public:
	Powerup(double xx, double yy) : x(xx), y(yy), Vy(POWERUP_SPEED) { }
	
	static void Destroy(Powerup *aux) {
		for (int i = 0; i < GameField::getInstance().PowerupList.size(); i++) {
			if ((GameField::getInstance()).PowerupList[i] == aux) {
				GameField::getInstance().PowerupList.erase(GameField::getInstance().PowerupList.begin() + i);
				delete aux;
				aux = 0;
				
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
		else if (ynew > SCREEN_HEIGHT)
			return -1;	//returning information to be removed
		return 1;
	}

	static void MoveAll(float timeStep) {
		for (int i = 0; i < GameField::getInstance().PowerupList.size(); i++) {
			if ((GameField::getInstance()).PowerupList[i]->Move(timeStep) == -1) {
				Destroy((GameField::getInstance()).PowerupList[i]);
			}
		}
	}


	
	double x, y, Vy;
};

class TripleBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < Ball::BallList.size(); i++) {
			if (!Ball::BallList.empty()) {
				Ball::BallList[i]->MultiplyBalls(TRIPLE_PWUP_BALL_NUMBER, *(Ball::BallList[i]));
			}
			Destroy(this);
		}
	}

	





};

class BigBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < Ball::BallList.size(); i++) {
			Ball::BallList[i]->radius *= BIGBALL_PWUP_RADIUS_MULTIPLER;
		}
		Destroy(this);
	}

	BigBallPWUP(double xx, double yy) : Powerup(xx, yy) {}
};

class ShootPWUP : public Powerup {
public:
	//TODO:
	//void Collect();
};

class ExtraLivePWUP : public Powerup {
public:
	void Collect() {
		(Player::getInstance()).lives += EXTRALIVE_PWUP_LIVE_AMT;
		Destroy(this);
	}

};

class BigRacketPWUP : public Powerup {
public:
	void Collect() {
		(Racket::getInstance()).width *= BIGRACKET_PWUP_INCRASE;
		Destroy(this);
	}
};

class SmallRacketPWUP : public Powerup {
public:
	void Collect() {
		(Racket::getInstance()).width *= SMALLRACKET_PWUP_DECRASE;
		Destroy(this);
	}
};

class FastBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < Ball::BallList.size(); i++) {
			Ball::BallList[i]->Vx *= FASTBALL_PWUP_INCRASE;
			Ball::BallList[i]->Vy *= FASTBALL_PWUP_INCRASE;
		}
		Destroy(this);
	}
};

class SlowBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < Ball::BallList.size(); i++) {
			Ball::BallList[i]->Vx *= SLOWBALL_PWUP_DECRASE;
			Ball::BallList[i]->Vy *= SLOWBALL_PWUP_DECRASE;
		}
		Destroy(this);
	}
};