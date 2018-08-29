#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Texturee.h"
#include "Monster.h"

class Bullett :public Texturee
{
public:
	Bullett(sf::Texture &textureB, float x, float y);
	~Bullett();

	bool explosion(Monster *monster, int offence);
	bool checkCollisionMonster(Monster* monst);
};

