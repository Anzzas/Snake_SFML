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
		, m_previousMenu{ MenuType::main_menu }
	{
	}


	void navigate(MenuType menuType, const sf::Event::KeyPressed* keyEvent, DifficultyMode& currentDifficulty);


	const MenuSelection& getCurrentSelection() const { return m_currentSelection; }


	const MenuType& getCurrentMenu() const { return m_currentMenu; }


	const MenuType& getPreviousMenu() const { return m_previousMenu; }

	
	void setCurrentMenu(MenuType menuType) 
	{ 
		m_previousMenu = m_currentMenu;
		m_currentMenu = menuType;
		m_currentSelection = menuType == MenuType::difficulty_menu ? MenuSelection::easy : MenuSelection::play;
	}

private:

	MenuSelection& getNewSelection(MenuSelection& selection, MenuType menuType, DifficultyMode& difficulty, const sf::Event::KeyPressed* keyEvent);


	MenuSelection m_currentSelection;


	MenuType m_currentMenu;


	MenuType m_previousMenu;
};

#endif