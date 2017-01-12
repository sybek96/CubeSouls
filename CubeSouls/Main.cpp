#include "Game.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 33u;
	Game& game = Game(settings);
	game.run();
}