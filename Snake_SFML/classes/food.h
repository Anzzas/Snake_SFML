#ifndef FOOD_H
#define FOOD_H
#include "random.h"
#include "common.h"

class Food
{
public:

	Food() = default;

	Food(Position pos)
		: m_pos{ pos }
	{
	}


	/** Give the new random position on this Food object*/
	void generate(Position randomPosition) { m_pos = randomPosition; }


	const Position& getPos() const { return m_pos; }

private:

	Position m_pos{};
};

#endif