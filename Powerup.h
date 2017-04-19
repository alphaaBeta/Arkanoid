#pragma once

#include "Config.h"

#include "Ball.h"
#include "Player.h"
#include "Racket.h"

Ball *BallArray[BALL_LIMIT];

class Powerup
{
public:
	Powerup(double xx, double yy) : x(xx), y(yy), Vy(-0.5) {}
	~Powerup() { delete this; }

	void Collect() {}

	void Move() {
		double ynew = y + (y*Vy);
		if (GetDistanceFromLine(ynew, (Racket::getInstance().y)) <= POWERUP_COLLECT_RANGE) {
			if (GetDistanceFromLine(x, (Racket::getInstance().x)) <= ((Racket::getInstance()).width / 2 + POWERUP_COLLECT_RANGE)) {
				this->Collect();
			}
		}
		else if (ynew > 0) {
			y = ynew;
		}
		else
			this->~Powerup();	//calling destr. when falling out of gamefield
	}

	double x, y, Vy;
};

class TripleBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < BALL_LIMIT; i++) {
			if (BallArray[i]) {
				BallArray[i]->MultiplyBalls(TRIPLE_PWUP_BALL_NUMBER, *(BallArray[i]));
			}
		}
	}


};

class BigBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < BALL_LIMIT; i++) {
			BallArray[i]->radius *= BIGBALL_PWUP_RADIUS_MULTIPLER;
		}
	}
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
	}
};

class BigRacketPWUP : public Powerup {
public:
	void Collect() {
		(Racket::getInstance()).width *= BIGRACKET_PWUP_INCRASE;
	}
};

class SmallRacketPWUP : public Powerup {
public:
	void Collect() {
		(Racket::getInstance()).width *= SMALLRACKET_PWUP_DECRASE;
	}
};

class FastBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < BALL_LIMIT; i++) {
			BallArray[i]->Vx *= FASTBALL_PWUP_INCRASE;
			BallArray[i]->Vy *= FASTBALL_PWUP_INCRASE;
		}
	}
};

class SlowBallPWUP : public Powerup {
public:
	void Collect() {
		for (int i = 0; i < BALL_LIMIT; i++) {
			BallArray[i]->Vx *= SLOWBALL_PWUP_DECRASE;
			BallArray[i]->Vy *= SLOWBALL_PWUP_DECRASE;
		}
	}
};