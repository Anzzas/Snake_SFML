#include "../classes/game.h"

int main()
{

	while (true)
	{
		auto window{ std::make_unique<sf::RenderWindow>(DisplaySettings::window_Dimensions, DisplaySettings::window_Dimensions, DisplaySettings::windowName) };
		
		window->setVerticalSyncEnabled(true);

		std::unique_ptr<Snake> snake{ std::make_unique<Snake>() };

		std::unique_ptr<Food> food{ std::make_unique<Food>(Position::createRandomPosition(snake->getBody())) };

		std::unique_ptr<Board> board{ std::make_unique<Board>() };

		std::unique_ptr<Display> display{ std::make_unique<Display>() };

		std::unique_ptr<PlayerController> playerController{ std::make_unique<PlayerController>() };

		std::unique_ptr<Menu> menu{ std::make_unique<Menu>() };


		Game game{std::move(window), std::move(board), std::move(snake), std::move(food), std::move(playerController), std::move(display), std::move(menu) };

		game.run();

		if (!game.replayGame())
			break;
	}
}