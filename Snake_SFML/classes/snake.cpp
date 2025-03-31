#include "snake.h"

void Snake::move(Direction direction)
{
	Position newHeadPos{ m_body.front() };

	switch (direction)
	{
	case Direction::up:
		newHeadPos.y -= 1;
		m_direction = Direction::up;
		break;
	case Direction::right:
		newHeadPos.x += 1;
		m_direction = Direction::right;
		break;
	case Direction::down:
		newHeadPos.y += 1;
		m_direction = Direction::down;
		break;
	case Direction::left:
		newHeadPos.x -= 1;
		m_direction = Direction::left;
		break;
	}

	for (size_t i = m_body.size() - 1; i > 0; i--)
		m_body[i] = m_body[i - 1];

	m_body[0] = newHeadPos;
}

void Snake::grow()
{
	// Getting last two segments
	const Position& lastPos = m_body.back();
	const Position& secondLastPos = m_body[m_body.size() - 2];


	// Getting the movement direction of the tail
	int dx{ static_cast<int>(lastPos.x) - static_cast<int>(secondLastPos.x) };
	int dy{ static_cast<int>(lastPos.y) - static_cast<int>(secondLastPos.y) };

	// Create a new segment in the same direction
	Position newBodyPartPos{ lastPos.y + dy, lastPos.x + dx };

	// Verifying that the new segment's position is valid
	if (newBodyPartPos.x > 0 && newBodyPartPos.x < Settings::boardWidth - 1 &&
		newBodyPartPos.y > 0 && newBodyPartPos.y < Settings::boardHeight - 1)
		m_body.push_back(newBodyPartPos);
}