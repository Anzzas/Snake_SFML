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

	Game(std::unique_ptr<Board> board, std::unique_ptr<Snake> snake, std::unique_ptr<Food> food, std::unique_ptr<PlayerController> controller, std::unique_ptr<Display> display, std::unique_ptr<Menu> menu)
		: m_board{ std::move(board) }
		, m_snake{ std::move(snake) }
		, m_food{ std::move(food) }
		, m_controller{ std::move(controller) }
		, m_display{ std::move(display) }
		, m_menu{ std::move(menu) }
		, m_score{}
		, m_isRunning{ true }
		, m_eatBuffer{}
		, m_eatSound{ m_eatBuffer }
	{
		m_food->generate(Position::createRandomPosition(m_snake->getBody()));

		if (!m_eatBuffer.loadFromFile("audio/beep.mp3"))
		{
			// Gérer l'erreur de chargement
			std::cout << "Cannot load beep.mp3\n";
		}
		m_eatSound.setBuffer(m_eatBuffer);
	}


	/** Main Game function where everything runs*/
	void run();


	bool replayGame(/*const std::optional<sf::Event>& event*/);

private:

	std::unique_ptr<Board> m_board;
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Food> m_food;
	std::unique_ptr<PlayerController> m_controller;
	std::unique_ptr<Display> m_display;
	std::unique_ptr<Menu> m_menu;
	int m_score;
	bool m_isRunning;
	sf::RenderWindow m_window;
	sf::SoundBuffer m_eatBuffer;
	sf::Sound m_eatSound;


	void createWindow();


	/** Collision CHECK for BORDERS and Snake's BODY*/
	bool checkCollision() const;


	/** Score handling
	* Detecting whether the Snake's head has the same Position as the Food (collision)
	* Then add points to the score
	* Then generating a new Position for the food
	* And growing the Snake body by ONE */
	void handleScore();


	void play();
};

#endif