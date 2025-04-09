#ifndef MENU_H
#define MENU_H
#include "common.h"
#include <SFML/Window.hpp>

class Menu
{
public:

	Menu()
		: m_currentSelection{ MenuSelection::play }
		, m_currentMenu{ MenuType::main_menu }
	{
	}


	void navigate(MenuType menuType, const sf::Event::KeyPressed* keyEvent, DifficultyMode& currentDifficulty);


	const MenuSelection& getCurrentSelection() const { return m_currentSelection; }


	const MenuType& getCurrentMenu() const { return m_currentMenu; }

	
	void setCurrentMenu(MenuType menuType) 
	{ 
		m_currentMenu = menuType;
		m_currentSelection = menuType == MenuType::difficulty_menu ? MenuSelection::easy : MenuSelection::play;
	}

private:

	MenuSelection& getNewSelection(MenuSelection& selection, MenuType menuType, DifficultyMode& difficulty, const sf::Event::KeyPressed* keyEvent);


	MenuSelection m_currentSelection;


	MenuType m_currentMenu;
};

#endif