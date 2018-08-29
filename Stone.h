#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Texturee.h"

class Stone : public Texturee
{
public:
	Stone(sf::Texture &texture, int x, int y);
	~Stone();
};