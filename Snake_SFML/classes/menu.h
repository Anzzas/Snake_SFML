#ifndef MENU_H
#define MENU_H
#include "common.h"
#include <SFML/Window.hpp>

class Menu
{
public:

	Menu() = default;


	void navigate(MenuType menuType, const sf::Event::KeyPressed* keyEvent, DifficultyMode& currentDifficulty);

private:

	MenuSelection& getNewSelection(MenuSelection& selection, MenuType menuType, DifficultyMode& difficulty, const sf::Event::KeyPressed* keyEvent);


	const MenuSelection& getCurrentSelection() const { return m_currentSelection; }


	MenuSelection m_currentSelection;


	MenuType m_currentMenu;


	bool m_firstSelection{ true };
};

#endif