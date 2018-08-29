#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Texturee.h"


class Path : public Texturee
{
public:
	Path(sf::Texture &texture, int x, int y);
	~Path();
};