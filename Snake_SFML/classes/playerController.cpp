#include "playercontroller.h"
#include <SFML/Window/Event.hpp>


/** Getting the input direction
* Returns the current direction if an opposite direction key is pressed
* Manage ESCAPE key case if the player wants to quit the game
*/
Direction PlayerController::getDirection(Direction currentDirection, const sf::Event::KeyPressed* keyEvent)
{

	switch (keyEvent->scancode)
	{
	case sf::Keyboard::Scan::Up:
		if (currentDirection != Direction::down)
			return Direction::up;
		break;

	case sf::Keyboard::Scan::Right:
		if (currentDirection != Direction::left)
			return Direction::right;
		break;

	case sf::Keyboard::Scan::Down:
		if (currentDirection != Direction::up)
			return Direction::down;
		break;

	case sf::Keyboard::Scan::Left:
		if (currentDirection != Direction::right)
			return Direction::left;
		break;

	case sf::Keyboard::Scan::Escape:
		m_isQuitting = true;
		[[fallthrough]];

	default: return currentDirection;
	}
}


//* Returns whether the player has pressed ESCAPE key to QUIT or not
const bool& PlayerController::isQuitReq() const
{
	return m_isQuitting;
}