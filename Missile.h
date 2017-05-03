#pragma once
#include <vector>

#include "Config.h"
#include "GameField.h"
#include "Block.h"


class Missile {
public:

	Missile();
	~Missile();
	Missile(double, double);

	char Move(float timeStep);

	Block* CheckCollision();
		
	void Destroy();

	static void MoveAll(float timeStep);




	static std::vector<Missile *> MissileList;

	double x, y, Vy;
};
