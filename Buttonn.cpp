//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#include "Buttonn.h"

Buttonn::Buttonn(sf::Texture &texture, towerType value, int x, int y)
{
	sprite.setTexture(texture);
	butSize = texture.getSize();
	butSize.y /= 2;
	sprite.setTextureRect(sf::IntRect(butSize.x * 0, butSize.y * 0, butSize.x, butSize.y));

	//kwadrat pokazujacy miejca, gdzie mozna postawic wieze
	shape.setSize(sf::Vector2f(50.0f, 50.0f));
	shape.setFillColor(sf::Color(255, 255, 255, 150));

	type = value;

	sprite.setPosition(x, y);
}

Buttonn::~Buttonn()
{
}

void Buttonn::updatebutton(sf::RenderWindow &window, int x, int y) //funkcja uaktualniajaca wyglad przycisku
{
	sf::Vector2f temp = buttonCoord();
	if (x >= temp.x && x < temp.x + 50 && y <= temp.y + 50 && y > temp.y)
		sprite.setTextureRect(sf::IntRect(butSize.x * 0, butSize.y * 1, butSize.x, butSize.y));
	else
		sprite.setTextureRect(sf::IntRect(butSize.x * 0, butSize.y * 0, butSize.x, butSize.y));
}

void Buttonn::changeShape(char color, int x, int y)
{
	if (color == 'w')
		shape.setFillColor(sf::Color(255, 255, 255, 150));
	else
		shape.setFillColor(sf::Color(255, 0, 0, 150));
	shape.setPosition(x, y);
}

void Buttonn::changeShapeT(bool value)
{
	shapeT = value;
}

void Buttonn::changeClick(bool value)
{
	click = value;
}

void Buttonn::changeUpgrade(bool value)
{
	upgrade = value;
}

bool Buttonn::clickF()
{
	return click;
}

bool Buttonn::shapeTF()
{
	return shapeT;
}

bool Buttonn::getUpgrade()
{
	return upgrade;
}

sf::Vector2f Buttonn::buttonCoord()
{
	return getPosition();
}

sf::Sprite &Buttonn::getButton()
{
	return sprite;
}

sf::RectangleShape &Buttonn::getShape()
{
	return shape;
}

int Buttonn::getType()
{
	return type;
}

void Buttonn::ifPressed(sf::RenderWindow &window) //funkcja dzieki ktorej mozna przenosic wiez na pole
{
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	sf::Vector2f temp = buttonCoord();
	updatebutton(window, mouse.x, mouse.y); //aktualizacja przycisku wiezy (podswietlony/nie)

	if (sf::Event::MouseButtonReleased && 
		sf::Mouse::isButtonPressed(sf::Mouse::Left)  //jezeli mysz jest nacisnieta
		&& mouse.x >= temp.x && mouse.x <= temp.x + 50 &&
		mouse.y <= temp.y + 50 && mouse.y >= temp.y)
	{
		click = true;
	}	
}

int Buttonn::enoughMoney(int towerType, int money)
{
	if (towerType == 0)
	{
		if (money < Tower_apple::price)
			return 0;
		else
			return Tower_apple::price;
	}

	else if (towerType == 1)
	{
		if (money < Tower_orange::price)
			return 0;
		else
			return Tower_orange::price;
	}
	else if (towerType == 2)
	{
		if (money < Tower_wmelon::price)
			return 0;
		else
			return Tower_wmelon::price;
	}
	else if (towerType == 3)
	{
		if (money < Tower_straw::price)
			return 0;
		else
			return Tower_straw::price;
	}
}

