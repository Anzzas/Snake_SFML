#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "snake.h"
#include "food.h"
#include "playerController.h"
#include "display.h"
#include "menu.h"
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

namespace GameSettings
{
	inline const std::map<DifficultyMode, float> difficultyMap{
	{DifficultyMode::easy, 0.1f},
	{DifficultyMode::medium, 0.075f},
	{DifficultyMode::hard, 0.05f} };

	inline DifficultyMode currentDifficulty{ DifficultyMode::medium };

	inline float tickRate = difficultyMap.at(currentDifficulty);

	constexpr int addScore{ 50 };

	constexpr double loadingTime{ 1.5 };
}

class Game
{
public:

	Game(std::unique_ptr<sf::RenderWindow> window, std::unique_ptr<Board> board, std::unique_ptr<Snake> snake, std::unique_ptr<Food> food, std::unique_ptr<PlayerController> controller, std::unique_ptr<Display> display, std::unique_ptr<Menu> menu)
		: m_window{ std::move(window) }
		, m_board{ std::move(board) }
		, m_snake{ std::move(snake) }
		, m_food{ std::move(food) }
		, m_controller{ std::move(controller) }
		, m_display{ std::move(display) }
		, m_menu{ std::move(menu) }
		, m_score{}
		, m_highScore{}
		, m_isRunning{ true }
		, m_eatBuffer{}
		, m_newHighBuffer{}
		, m_eatSound{ m_eatBuffer }
		, m_newHigh{ m_newHighBuffer }
	{
		m_food->generate(Position::createRandomPosition(m_snake->getBody()));

		if (!m_eatBuffer.loadFromFile("audio/beep.mp3"))
			std::cout << "Cannot load beep.mp3\n";

		if (!m_newHighBuffer.loadFromFile("audio/beep2.mp3"))
			std::cout << "Cannot load beep2.mp3\n";

		m_eatSound.setBuffer(m_eatBuffer);

		m_newHigh.setBuffer(m_newHighBuffer);

		loadHighScore();
	}


	/** Main Game function where everything runs*/
	void run();


	bool replayGame();

private:

	std::unique_ptr<sf::RenderWindow> m_window;
	std::unique_ptr<Board> m_board;
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Food> m_food;
	std::unique_ptr<PlayerController> m_controller;
	std::unique_ptr<Display> m_display;
	std::unique_ptr<Menu> m_menu;
	int m_score;
	int m_highScore;
	bool m_isRunning;
	sf::SoundBuffer m_eatBuffer;
	sf::SoundBuffer m_newHighBuffer;
	sf::Sound m_eatSound;
	sf::Sound m_newHigh;


	/** Collision CHECK for BORDERS and Snake's BODY*/
	bool checkCollision() const;


	/** Score handling
	* Detecting whether the Snake's head has the same Position as the Food (collision)
	* Then add points to the score
	* Then generating a new Position for the food
	* And growing the Snake body by ONE */
	void handleScore();


	void play();


	void loadHighScore();


	void saveHighScore();
};

#endif