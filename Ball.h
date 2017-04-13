#pragma once



class Ball
{
public:
	Ball() { BallAmmount++; };
	~Ball();

	/////////////////////
	//----MAIN VARS----//
	/////////////////////

	static int BallAmmount;
	double x, y, vx, vy;
	inline double V();

	////////////////////////
	//----MAIN METHODS----//
	////////////////////////

	int CheckCollision();
	void Move();

	//TODO:
	//-checks for bonuses player has 

};

