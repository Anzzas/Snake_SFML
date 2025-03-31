#ifndef SNAKE_H
#define SNAKE_H
#include "common.h"
#include <deque>

namespace SnakeSettings
{
	constexpr size_t y_SnakeStart{ Settings::boardHeight / 2 };
	constexpr size_t x_SnakeStart{ 2 };
}

using namespace SnakeSettings;

class Snake
{
public:

	Snake() = default;

	/** Main move function based on the direction from PlayerController*/
	void move(Direction direction);


	/** Grow the snake from the tail by one after collision with Food*/
	void grow();


	const std::deque<Position>& getBody() const { return m_body; }


	const Direction& getDirection() const { return m_direction; }

private:

	std::deque<Position> m_body{
	Position{y_SnakeStart, x_SnakeStart + 3}, // HEAD
	Position{y_SnakeStart, x_SnakeStart + 2},
	Position{y_SnakeStart, x_SnakeStart + 1},
	Position{y_SnakeStart, x_SnakeStart} // TAIL
	};

	Direction m_direction{ Direction::right }; // DEFAULT DIRECTION
};

#endif