#include "menu.h"

void Menu::navigate(MenuType menuType, const sf::Event::KeyPressed* keyEvent, DifficultyMode& currentDifficulty)
{
	m_currentSelection = getNewSelection(m_currentSelection, m_currentMenu, currentDifficulty, keyEvent);
}


MenuSelection& Menu::getNewSelection(MenuSelection& currentSelection, MenuType menuType, DifficultyMode& difficulty, const sf::Event::KeyPressed* keyEvent)
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

	return currentSelection;
}