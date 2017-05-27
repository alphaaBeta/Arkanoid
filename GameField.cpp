#include "GameField.h"

#include "Block.h"


std::vector<Block *> GameField::blockList;
std::vector<Powerup *> GameField::powerupList;

int GameField::AddBlock(int x, int y, BlockType type, Colour colour) {

	if (blockMatrix[x][y] && type!=NONE) { return 0; }
	
	switch (type) {

	case NONE:
		//Remove the block
		for (int i = 0; i < blockList.size(); i++)
			if (blockList[i] == blockMatrix[x][y]) 
				blockList.erase\
					(blockList.begin() + i);

		delete blockMatrix[x][y];
		blockMatrix[x][y] = 0;
		return 1;
	case REGULAR:
		blockMatrix[x][y] = new RegularBlock;		
		break;
	case STRONG:
		blockMatrix[x][y] = new StrongBlock;
		break;
	case VERY_STRONG:
		blockMatrix[x][y] = new VeryStrongBlock;
		break;
	case INDESTRUCTIBLE:
		blockMatrix[x][y] = new IndestructibleBlock;
		break;
	}

	//Set block's x and y to some specific pixel value
	blockMatrix[x][y]->x = x*BLOCK_WIDTH;
	blockMatrix[x][y]->y = y*BLOCK_HEIGHT;

	//Set colour if one is given
	if (colour.a) {
		blockMatrix[x][y]->colour = colour;
	}
	
	//Add a pointer to the block to the end of the list
	blockList.push_back(blockMatrix[x][y]);

	
	return 1;
	
}

void GameField::PurgeBlocks() {

	for (int x = 0; x < FIELD_WIDTH; x++) {
		for (int y = 0; y < FIELD_HEIGHT; y++) {
			blockMatrix[x][y] = 0;
		}
	}
	while (blockList.size()) {
		delete blockList.back();
		blockList.pop_back();
	}

}

bool GameField::IsClear() {
	return(blockList.empty());

}
