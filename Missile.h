#pragma once
#include <vector>

#include "Config.h"
#include "GameField.h"
#include "Block.h"


class Missile {
public:

	/**
	* \brief Creates a missile at 0,0
	*/
	Missile();
	/**
	* \brief Removes missile from missileList
	*/
	~Missile();
	/**
	* \brief Creates a missile with set coordinates
	*
	* \param double X position in gamefield
	* \param double Y position in gamefield
	* \param int Missile speed. Negative numbers make missile go up.
	*/
	Missile(double, double, int = -MISSILE_SPEED);


	/**
	* \brief X coordinate.
	*/
	double x;


	/**
	* \brief Y coordinate.
	*/
	double y;


	/**
	* \brief Vertical speed.
	*/
	double Vy;


	/**
	* \brief Calculates new position based on timeStep, checks collision.
	*
	* \param float timeStep
	*
	* \return -1 If a boundary or object has been hit.
	* \return 1 else
	*/
	char Move(float timeStep);


	/**
	* \brief Checks for collision with blocks.
	*
	* \return Block* a pointer to block that has been hit.
	*/
	Block* CheckCollision();
		

	/**
	* Function checks if Move() call on missiles resulted in -1. If it did, missile gets destroyed.
	*
	* \brief Moves all the missiles in missileList
	*
	* \param float timeStep
	*/
	static void MoveAll(float timeStep);


	/**
	* \brief A list of pointers to all missiles.
	*/
	static std::vector<Missile *> missileList;



};
