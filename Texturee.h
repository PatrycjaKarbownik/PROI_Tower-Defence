#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Texturee : public sf::Drawable, sf::Transformable //rodzic wszystkich teksturowych klas
{
public:
	Texturee();
	~Texturee();

	void setPosition(float x, float y);
	void move(float x, float y);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	sf::Vector2f getPosition();
	sf::FloatRect getBoundingBox();

protected:
	sf::Texture texture;
	sf::Sprite sprite;
	bool show;
};