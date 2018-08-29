#include "Texturee.h"

Texturee::Texturee() //rodzic wszystkich teksturowych klas
{
}

Texturee::~Texturee()
{
}

sf::FloatRect Texturee::getBoundingBox()
{
	return sprite.getGlobalBounds();
}

void Texturee::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite);
}

sf::Vector2f Texturee::getPosition()
{
	return sprite.getPosition();
}

void Texturee::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Texturee::move(float x, float y)
{
	sprite.move(x, y);
}