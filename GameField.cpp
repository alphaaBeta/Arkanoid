#include "GameField.h"

#include "Block.h"

int GameField::AddBlock(int x, int y, BlockType type, int colour) {

	if (!BlockMatrix[x][y]) { return 0; }
	
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

	BlockMatrix[x][y]->colour = colour;

	for (int i = 2; i <= BlockMatrix[x][y]->sizeX; i++) {	//for different sizes
		BlockMatrix[x + i - 1][y] = BlockMatrix[x][y];
		if (BlockMatrix[x][y]->sizeY != 1) {
			for (int j = 2; j <= BlockMatrix[x][y]->sizeY; j++) {
				BlockMatrix[x + i - 1][y + j -1] = BlockMatrix[x][y];
			}
		}
	}
	
}