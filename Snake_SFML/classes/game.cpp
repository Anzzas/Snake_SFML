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

			if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
			{
				m_menu->navigate(MenuType::main_menu, keyEvent, GameSettings::currentDifficulty);

				m_display->renderMenu(m_window, m_score, m_controller->getInput(keyEvent), MenuType::main_menu, GameSettings::currentDifficulty);
			}
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


/*bool Game::replayGame(const std::optional<sf::Event>& event)
{

	return openMenu(MenuType::replay_menu, event);
}*/