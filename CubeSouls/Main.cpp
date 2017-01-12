#include "Game.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0u;
	Game& game = Game(settings);
	game.run();
}