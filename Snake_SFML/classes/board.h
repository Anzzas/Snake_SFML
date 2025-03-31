#ifndef BOARD_H
#define BOARD_H
#include "common.h"

class Board
{
public:

	Board() = default;


	/** Checking if the position is in a wall or not*/
	bool isWall(const Position& pos) const;

private:

	int width{ Settings::boardWidth };
	int height{ Settings::boardHeight };
};

#endif
