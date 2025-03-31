#include "../classes/display.h"
#include "../classes/snake.h"
#include "../classes/food.h"

int main()
{
	Snake snake{};
	Food food{ Position{20, 20} };
	Display display{};


	display.renderGame(snake.getBody(), food.getPos());
}