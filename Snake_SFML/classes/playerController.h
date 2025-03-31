#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "common.h"
#include <optional>

/** Keyboard control manager*/
class PlayerController
{
public:

	PlayerController() = default;


	/** Converting inputs (arrow keys) into a Direction*/
	Direction getDirection(Direction snakeDirection);


	std::optional<Direction> getMenuDirection(const InputType& input) const;


	/** Detecting ESCAPE input and stop the game if pressed*/
	const bool& isQuitReq() const;


	bool hasPressedEnter() const;


	InputType getInput() const;

private:

	bool m_isQuitting{};
};

#endif