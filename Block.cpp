#include "Block.h"



void Block::Hit(int a = 1) {
	this->health-=a;
	if (health == 0 || (health == -1 && a == 2)) {
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