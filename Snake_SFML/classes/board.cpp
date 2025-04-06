#include "board.h"


bool Board::isWall(const Position& pos) const
{

    if (pos.x == 0 || pos.y == 0)
        return true;

    if (pos.x >= Settings::boardWidth || pos.y >= Settings::boardHeight)
        return true;

    return false;
}