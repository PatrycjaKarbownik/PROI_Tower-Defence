//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#pragma once
#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Texturee.h"

class River : public Texturee
{
public:
	River(int x, int y);
	~River();

	sf::RectangleShape &getShape();

private:
	sf::RectangleShape river;
};

