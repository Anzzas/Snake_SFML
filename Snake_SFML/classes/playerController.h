#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "common.h"
#include <optional>
#include <SFML/Window/Event.hpp>

/** Keyboard control manager*/
class PlayerController
{
public:

	PlayerController() = default;


	/** Converting inputs (arrow keys) into a Direction*/
	Direction getDirection(Direction currentDirection, const sf::Event::KeyPressed* keyEvent);


	/** Detecting ESCAPE input and stop the game if pressed*/
	const bool& isQuitReq() const;

private:

	bool m_isQuitting{};
};

#endif