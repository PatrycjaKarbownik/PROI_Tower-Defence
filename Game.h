#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Engine.h"
#include "Save.h"

class Game: public Save
{
public:
	Game();
	~Game();

	void runGame();
	void menu(sf::RenderWindow &window);
	void single(sf::RenderWindow &window);
	void gameOver(sf::RenderWindow &window);
	void load();

private:
	sf::Font font;
	sf::Font rusFont;
	sf::Font goFont;
	sf::Text head;

	enum GameState { MENU, GAME, GAME_OVER, END, LOAD };
	GameState state;
	Engine *engine;
};

