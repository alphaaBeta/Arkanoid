#include "Block.h"



void Block::Hit(int a) {
	this->health-=a;
	if (health == 0 || (health == -1 && a == 2)) {
		this->Destroy();
	}
	else if (health < 0) {	//indestructible blocks remain indestructible
		health = 0;
	}
}

void Block::Destroy() {
	
	//Random chance of dropping a powerup
	if (rand() % 10 < 10) {
		Powerup *aux;
		int a = 2; //rand() % 8;
		switch (a) {
		case 0:
			aux = new BigBallPWUP(double(this->x), double(this->y));
			break;
		case 1:
			aux = new TripleBallPWUP(double(this->x), double(this->y));
			break;
		case 2:
			aux = new ShootPWUP(double(this->x), double(this->y));
			break;
		case 3:
			aux = new ExtraLivePWUP(double(this->x), double(this->y));
			break;
		case 4:
			aux = new BigRacketPWUP(double(this->x), double(this->y));
			break;
		case 5:
			aux = new SmallRacketPWUP(double(this->x), double(this->y));
			break;
		case 6:
			aux = new FastBallPWUP(double(this->x), double(this->y));
			break;
		case 7:
			aux = new SlowBallPWUP(double(this->x), double(this->y));
			break;
		}

		
		GameField::getInstance().PowerupList.push_back(aux);
	}

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

	delete this;
}