#pragma once
#include <vector>

#include "Config.h"
#include "GameField.h"
#include "Block.h"


class Missile {
public:

	Missile();
	~Missile();
	Missile(double, double, int = -MISSILE_SPEED);

	char Move(float timeStep);

	Block* CheckCollision();
		

	static void MoveAll(float timeStep);




	static std::vector<Missile *> missileList;

	double x, y, Vy;
};
