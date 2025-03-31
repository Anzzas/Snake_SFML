#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "snake.h"
#include "food.h"
#include "playerController.h"
#include "display.h"
#include <map>

namespace GameSettings
{
	inline const std::map<DifficultyMode, double> difficultyMap{
	{DifficultyMode::easy, 0.1},
	{DifficultyMode::medium, 0.05},
	{DifficultyMode::hard, 0.03} };

	inline DifficultyMode currentDifficulty{ DifficultyMode::easy };

	inline double gameSpeed{ difficultyMap.at(currentDifficulty) };

	constexpr int addScore{ 50 };
	constexpr double loadingTime{ 1.5 };
}

class Game
{
public:

	Game(std::unique_ptr<Board> board, std::unique_ptr<Snake> snake, std::unique_ptr<Food> food, std::unique_ptr<PlayerController> controller, std::unique_ptr<Display> display)
		: m_board{ std::move(board) }
		, m_snake{ std::move(snake) }
		, m_food{ std::move(food) }
		, m_controller{ std::move(controller) }
		, m_display{ std::move(display) }
		, m_score{}
		, m_isRunning{ true }
	{
		m_food->generate(Position::createRandomPosition(m_snake->getBody()));
	}


	/** Main Game function where everything runs*/
	void run();


	bool replayGame() const;

private:

	std::unique_ptr<Board> m_board;
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Food> m_food;
	std::unique_ptr<PlayerController> m_controller;
	std::unique_ptr<Display> m_display;
	int m_score;
	bool m_isRunning;


	/** Loop where everythings in updated every frame (Render, Score, objects Positions)*/
	void update();


	/** Collision CHECK for BORDERS and Snake's BODY*/
	bool checkCollision() const;


	/** Score handling
	* Detecting whether the Snake's head has the same Position as the Food (collision)
	* Then add points to the score
	* Then generating a new Position for the food
	* And growing the Snake body by ONE */
	void handleScore();


	MenuSelection& getMenuSelection(MenuSelection& selection, MenuType menuType, DifficultyMode& difficulty) const;


	bool Menu(MenuType menuType) const;

};

#endif