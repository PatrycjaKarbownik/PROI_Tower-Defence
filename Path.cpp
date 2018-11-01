//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#include "Path.h"

Path::Path(sf::Texture &texture, int x, int y)
{
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

Path::~Path()
{
}