#include "../classes/game.h"

int main()
{
	std::unique_ptr<Snake> snake{std::make_unique<Snake>()};

	std::unique_ptr<Food> food{std::make_unique<Food>(Position::createRandomPosition(snake->getBody()))};

	std::unique_ptr<Board> board{std::make_unique<Board>()};

	std::unique_ptr<Display> display{std::make_unique<Display>()};

	std::unique_ptr<PlayerController> playerController{std::make_unique<PlayerController>()};


	Game game{ std::move(board), std::move(snake), std::move(food), std::move(playerController), std::move(display) };

	game.run();
}