#include "GameField.h"

#include "Block.h"


std::vector<Block *> GameField::BlockList;
std::vector<Powerup *> GameField::PowerupList;

int GameField::AddBlock(int x, int y, BlockType type, Colour colour) {

	if (BlockMatrix[x][y]) { return 0; }
	
	switch (type) {

	case REGULAR:
		BlockMatrix[x][y] = new RegularBlock;		
		break;
	case STRONG:
		BlockMatrix[x][y] = new StrongBlock;
		break;
	case VERY_STRONG:
		BlockMatrix[x][y] = new VeryStrongBlock;
		break;
	case INDESTRUCTIBLE:
		BlockMatrix[x][y] = new IndestructibleBlock;
		break;
	}

	//Set block's x and y to some specific pixel value
	BlockMatrix[x][y]->x = x*BLOCK_WIDTH;
	BlockMatrix[x][y]->y = y*BLOCK_HEIGHT;

	//Set colour if one is given
	if (colour.a) {
		BlockMatrix[x][y]->colour = colour;
	}
	
	//Add a pointer to the block to the end of the list
	BlockList.push_back(BlockMatrix[x][y]);

	
	return 1;
	
}
