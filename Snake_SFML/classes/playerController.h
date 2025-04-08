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


	void processEvent(const sf::Event& event);


	/** Converting inputs (arrow keys) into a Direction*/
	Direction getDirection(Direction currentDirection, const std::optional<sf::Event>& event);


	std::optional<Direction> getMenuDirection(const std::optional<sf::Event>& event) const;


	/** Detecting ESCAPE input and stop the game if pressed*/
	const bool& isQuitReq() const;


	bool hasPressedEnter() const;


	sf::Keyboard::Scancode getInput(const sf::Event::KeyPressed* keyEvent) const;

private:

	bool m_isQuitting{};
};

#endif