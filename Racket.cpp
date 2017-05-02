#include "Racket.h"

#include "Ball.h"


int Racket::Move(float timeStep) {


	
	this->x += this->speed * timeStep;
	 


	//Check for left side
	if (this->x < this->width / 2) {
		this->x = this->width / 2;
		return 0;
	}
	
	//Check for right side
	else if ((SCREEN_WIDTH - this->x) < (this->width / 2)) {
		this->x = SCREEN_WIDTH - (this->width / 2);
		return 0;
	}

	else {
		return 1;
	}


}