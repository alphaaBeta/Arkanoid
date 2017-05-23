#include "GameField.h"

#include "Block.h"


std::vector<Block *> GameField::blockList;
std::vector<Powerup *> GameField::powerupList;

int GameField::AddBlock(int x, int y, BlockType type, Colour colour) {

	if (blockMatrix[x][y]) { return 0; }
	
	switch (type) {

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
