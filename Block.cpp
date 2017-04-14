#include "Block.h"



void Block::Hit(int a) {
	this->health--;
	if (health == 0) {	
		this->Destroy();
	}
	else if (health < 0) {	//indestructible blocks remain indestructible
		health = 0;
	}
}

void Block::Destroy() {
	//TODO:
	//bonus drop
	this->~Block();
}