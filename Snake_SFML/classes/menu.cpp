#include "menu.h"

void Menu::navigate(MenuType menuType, const sf::Event::KeyPressed* keyEvent, DifficultyMode& currentDifficulty)
{
	// 1. définir la selection la première fois en fonction du type du menu
	if (m_firstSelection)
	{
		m_currentSelection = m_currentMenu == MenuType::difficulty_menu ? MenuSelection::easy : MenuSelection::play;
		m_firstSelection = false;
	}


	// 2. Avoir la nouvelle selection si le joueur appuis sur les touches directionelles
	m_currentSelection = getNewSelection(m_currentSelection, m_currentMenu, currentDifficulty, keyEvent);

	/*if (menuType == MenuType::difficulty_menu)
		GameSettings::gameSpeed = GameSettings::difficultyMap.at(GameSettings::currentDifficulty);*/
}


MenuSelection& Menu::getNewSelection(MenuSelection& currentSelection, MenuType menuType, DifficultyMode& difficulty, const sf::Event::KeyPressed* keyEvent)
{

	if (keyEvent->scancode == sf::Keyboard::Scancode::Up || keyEvent->scancode == sf::Keyboard::Scancode::Down)
	{

		if (menuType == MenuType::main_menu || menuType == MenuType::replay_menu)
		{

			switch (keyEvent->scancode)
			{
			case sf::Keyboard::Scancode::Up:

				switch (currentSelection)
				{
				case MenuSelection::play:
					return currentSelection = MenuSelection::quit;


				case MenuSelection::changeDifficulty:
					return currentSelection = MenuSelection::play;


				case MenuSelection::quit:
					return currentSelection = MenuSelection::changeDifficulty;
				}


				break;


			case sf::Keyboard::Scancode::Down:

				switch (currentSelection)
				{
				case MenuSelection::play:
					return currentSelection = MenuSelection::changeDifficulty;


				case MenuSelection::changeDifficulty:
					return currentSelection = MenuSelection::quit;


				case MenuSelection::quit:
					return currentSelection = MenuSelection::play;
				}


				break;
			}
		}



		else // If it's difficulty menu
		{

			switch (keyEvent->scancode)
			{
			case sf::Keyboard::Scancode::Up:

				switch (currentSelection)
				{
				case MenuSelection::easy:
					return currentSelection = MenuSelection::hard;


				case MenuSelection::medium:
					return currentSelection = MenuSelection::easy;


				case MenuSelection::hard:
					return currentSelection = MenuSelection::medium;
				}


				break;


			case sf::Keyboard::Scancode::Down:

				switch (currentSelection)
				{
				case MenuSelection::easy:
					return currentSelection = MenuSelection::medium;


				case MenuSelection::medium:
					return currentSelection = MenuSelection::hard;


				case MenuSelection::hard:
					return currentSelection = MenuSelection::easy;
				}
			}
		}
	}

	return currentSelection;
}

