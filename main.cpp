//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#include <ctime>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
	Game game;
	srand(time(NULL));
	game.runGame();

	return 0;
}