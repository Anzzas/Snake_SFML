#pragma once
#ifndef COMMON_H
#define COMMON_H
#include "random.h"
#include <deque>
#include <array>
#include <iostream>

namespace Settings
{
	constexpr int boardHeight{ 22 };
	constexpr int boardWidth{ 22 };
}

struct Position
{
	size_t y{};
	size_t x{};


	bool operator== (const Position& pos) const { return pos.x == x && pos.y == y; }


	/** Creating a random Position within the Board limits and outside the Snake's body*/
	static Position createRandomPosition(const std::deque<Position>& snakeBodyPos)
	{
		size_t y{ static_cast<size_t>(Random::get(1, Settings::boardHeight - 2)) };
		size_t x{ static_cast<size_t>(Random::get(1, Settings::boardWidth - 2)) };
		Position randomPos{ y, x };

		for (const auto& pos : snakeBodyPos)
		{
			if (randomPos == pos)
			{
				randomPos = Position::createRandomPosition(snakeBodyPos);
				continue;
			}
		}


		return randomPos;
	}
};


enum class Direction
{
	up,
	right,
	down,
	left,
	max_directions
};


enum class MenuSelection
{
	play,
	changeDifficulty,
	quit,
	easy,
	medium,
	hard,
	max_selections
};

enum class MenuType
{
	main_menu,
	replay_menu,
	difficulty_menu,
	max_menuTypes
};


enum class DifficultyMode
{
	easy,
	medium,
	hard,
	max_difficulties
};


inline std::ostream& operator<< (std::ostream& out, const DifficultyMode& mode)
{
	std::array<std::string, static_cast<size_t>(DifficultyMode::max_difficulties)> text{ "Easy", "Medium", "Hard" };

	out << text[static_cast<size_t>(mode)];

	return out;
}

#endif