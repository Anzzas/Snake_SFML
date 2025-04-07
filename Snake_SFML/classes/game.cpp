#include "game.h"


void Game::run()
{
	createWindow();


	m_display->renderMenu(m_window, m_score, sf::Keyboard::Scancode::Up, MenuType::main_menu, GameSettings::currentDifficulty); // Do once for the first frame


	while (m_window.isOpen())
	{
		while (auto event = m_window.pollEvent())
		{
			if (event->getIf<sf::Event::Closed>())
			{
				m_window.close();
				break;
			}

			if (event->getIf<sf::Event::KeyPressed>())
				Menu(MenuType::main_menu, event);
		}
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


MenuSelection& Game::getMenuSelection(MenuSelection& selection, MenuType menuType, DifficultyMode& difficulty, const std::optional<sf::Event>& event)
{

	while (true)
	{
		//InputType input{ m_controller->getInput(event) };
		sf::Keyboard::Scancode input{ m_controller->getInput(event) };


		if (input == sf::Keyboard::Scancode::Enter)
			return selection;


		if (input == sf::Keyboard::Scancode::Up || input == sf::Keyboard::Scancode::Down)
		{

			if (menuType == MenuType::main_menu || menuType == MenuType::replay_menu)
			{

				switch (input)
				{
				case sf::Keyboard::Scancode::Up:

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


				case sf::Keyboard::Scancode::Down:

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
				case sf::Keyboard::Scancode::Up:

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


				case sf::Keyboard::Scancode::Down:

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


		m_display->renderMenu(m_window, m_score, input, MenuType::replay_menu, difficulty);
	}
}


bool Game::openMenu(MenuType menuType, const std::optional<sf::Event>& event)
{

	MenuSelection selection{ menuType == MenuType::difficulty_menu ? MenuSelection::easy : MenuSelection::play };


	m_display->renderMenu(m_window, m_score, sf::Keyboard::Scancode::Up, menuType, GameSettings::currentDifficulty);


	selection = getMenuSelection(selection, menuType, GameSettings::currentDifficulty, event);


	//m_display->resetFlags();


	switch (selection)
	{
	case MenuSelection::play:
		return true;
	case MenuSelection::changeDifficulty:
		openMenu(MenuType::difficulty_menu, event);
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


bool Game::replayGame(const std::optional<sf::Event>& event)
{

	return Menu(MenuType::replay_menu, event);
}