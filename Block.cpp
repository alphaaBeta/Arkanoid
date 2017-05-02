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

	//Removes the block from the block list-vector
	for (int i = 0; i < (GameField::getInstance()).BlockList.size(); i++) {
		if ((GameField::getInstance()).BlockList[i] == this) {
			//Wowie
			(GameField::getInstance()).BlockList.erase\
				((GameField::getInstance()).BlockList.begin() + i);
		}
	}

	//Sets the block pointer to 0 on array.
	GameField::getInstance().BlockMatrix[this->x / BLOCK_WIDTH][this->y / BLOCK_HEIGHT] = 0;
}