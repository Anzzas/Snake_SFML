#include "board.h"


bool Board::isWall(const Position& pos) const
{
	if (pos.x == 0 || pos.x == Settings::boardWidth - 1 || pos.y == 0 || pos.y == Settings::boardHeight - 1)
		return true;

	return false;
}