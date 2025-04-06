#include "game.h"


void Game::run()
{
	createWindow();

	while (m_window.isOpen())
	{
		m_display->renderMenu(m_window, m_score, InputType::down_arrow, MenuType::main_menu, GameSettings::currentDifficulty);
	}

	/*
	sf::Clock clock;


	float timeBuffer{};


	Direction currentDirection = m_snake->getDirection();

	while (m_window.isOpen())
	{

		while (auto event = m_window.pollEvent())
		{

			if (event->getIf<sf::Event::Closed>())
			{
				m_window.close();
				break;
			}


			if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
			{

				currentDirection = m_controller->getDirection(currentDirection, event);


				if (m_controller->isQuitReq())
					m_window.close();
			}
		}


		float deltaTime{ clock.restart().asSeconds() };

		timeBuffer += deltaTime;

		if (timeBuffer >= GameSettings::tickRate)
		{

			m_snake->move(currentDirection);



			if (checkCollision())
			{
				m_window.close();
				break;
			}


			handleScore();


			timeBuffer -= GameSettings::tickRate;
		}


		m_display->renderGame(m_snake->getBody(), m_food->getPos(), m_score, m_window);
	}
	*/
}


bool Game::checkCollision() const
{
	// Check wall collision
	if (m_board->isWall(m_snake->getBody()[0]))
		return true;


	// Check Snake Body Collision
	for (size_t i = 1; i < m_snake->getBody().size(); i++)
	{
		if (m_snake->getBody()[0] == m_snake->getBody()[i])
			return true;
	}


	return false;
}


void Game::handleScore()
{
	if (m_snake->getBody()[0] == m_food->getPos())
	{
		m_score += GameSettings::addScore;

		m_food->generate(Position::createRandomPosition(m_snake->getBody()));

		m_snake->grow();

		m_eatSound.play();
	}
}


void Game::createWindow()
{
	m_window.create(sf::VideoMode({ DisplaySettings::window_Dimensions, DisplaySettings::window_Dimensions }), DisplaySettings::windowName);
	m_window.setVerticalSyncEnabled(true);
}


bool Game::isWindowOpen(const std::optional<sf::Event>& event)
{
	return !event->is<sf::Event::Closed>();
}


MenuSelection& Game::getMenuSelection(MenuSelection& selection, MenuType menuType, DifficultyMode& difficulty, const std::optional<sf::Event>& event) const
{

	while (true)
	{
		InputType input{ m_controller->getInput(event) };


		if (input == InputType::enter)
			return selection;


		if (input == InputType::up_arrow || input == InputType::down_arrow)
		{

			if (menuType == MenuType::main_menu || menuType == MenuType::replay_menu)
			{

				switch (input)
				{
				case InputType::up_arrow:

					switch (selection)
					{
					case MenuSelection::play:
						selection = MenuSelection::quit;
						break;


					case MenuSelection::changeDifficulty:
						selection = MenuSelection::play;
						break;


					case MenuSelection::quit:
						selection = MenuSelection::changeDifficulty;
						break;
					}


					break;


				case InputType::down_arrow:

					switch (selection)
					{
					case MenuSelection::play:
						selection = MenuSelection::changeDifficulty;
						break;


					case MenuSelection::changeDifficulty:
						selection = MenuSelection::quit;
						break;


					case MenuSelection::quit:
						selection = MenuSelection::play;
						break;
					}


					break;


				default: continue;
				}
			}



			else
			{

				switch (input)
				{
				case InputType::up_arrow:

					switch (selection)
					{
					case MenuSelection::easy:
						selection = MenuSelection::hard;
						break;


					case MenuSelection::medium:
						selection = MenuSelection::easy;
						break;


					case MenuSelection::hard:
						selection = MenuSelection::medium;
						break;
					}


					break;


				case InputType::down_arrow:

					switch (selection)
					{
					case MenuSelection::easy:
						selection = MenuSelection::medium;
						break;


					case MenuSelection::medium:
						selection = MenuSelection::hard;
						break;


					case MenuSelection::hard:
						selection = MenuSelection::easy;
						break;
					}


					break;


				default: continue;
				}
			}
		}


		//m_display->renderMenu(m_score, input, MenuType::replay_menu, difficulty);
	}
}


bool Game::Menu(MenuType menuType) const
{

	MenuSelection selection{ menuType == MenuType::difficulty_menu ? MenuSelection::easy : MenuSelection::play };


	//m_display->renderMenu(m_score, InputType::up_arrow, menuType, GameSettings::currentDifficulty); // Do once for the first frame


	//selection = getMenuSelection(selection, menuType, GameSettings::currentDifficulty);


	//m_display->resetFlags();


	switch (selection)
	{
	case MenuSelection::play:
		return true;
	case MenuSelection::changeDifficulty:
		Menu(MenuType::difficulty_menu);
		break;
	case MenuSelection::quit: return false;


	case MenuSelection::easy:
		GameSettings::currentDifficulty = DifficultyMode::easy;
		break;
	case MenuSelection::medium:
		GameSettings::currentDifficulty = DifficultyMode::medium;
		break;
	case MenuSelection::hard:
		GameSettings::currentDifficulty = DifficultyMode::hard;
	}


	if (menuType == MenuType::difficulty_menu)
		GameSettings::gameSpeed = GameSettings::difficultyMap.at(GameSettings::currentDifficulty);


	return true;
}


bool Game::replayGame() const
{

	return Menu(MenuType::replay_menu);
}