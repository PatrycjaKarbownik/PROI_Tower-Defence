//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#include "Stone.h"

Stone::Stone(sf::Texture &texture, int x, int y)
{
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

Stone::~Stone()
{
}
