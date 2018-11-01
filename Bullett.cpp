//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#include "Bullett.h"

Bullett::Bullett(sf::Texture &textureB, float x, float y)
{
	sprite.setTexture(textureB);
	sprite.setPosition(x,y);
}

Bullett::~Bullett()
{
}

bool Bullett::explosion(Monster * monster, int offence)
{
	if (checkCollisionMonster(monster) && !monster->isShoted()) //jesli potworek nadepnie na mine
	{
		monster->changeShoted(true);
		monster->changeStrength(/*monster->getStrength()-offence*/0);
		return true;
	}
	return false;
}

bool Bullett::checkCollisionMonster(Monster* monst)
{
	sf::FloatRect box(getBoundingBox());
	sf::FloatRect monster(monst->getBoundingBox());

	if(box.intersects(monster))	return true;

	return false;
}
