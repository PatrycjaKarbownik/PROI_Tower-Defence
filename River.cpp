#include "River.h"

River::River(int x, int y)
{
	river.setPosition(x, y);
	river.setSize(sf::Vector2f(150.0f, 50.0f));
}

River::~River()
{
}

sf::RectangleShape & River::getShape()
{
	return river;
}
