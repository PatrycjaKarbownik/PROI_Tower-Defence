#include "Cookie.h"
#include <string>
#include <iostream>

Cookie::Cookie()
{
	//pobranie teksturki pudelka
	if (!texture.loadFromFile("Dane/pudelko.png"))
	{
		std::cout << "Nie znaleziono tekstury!" << std::endl;
		return;
	}

	//pobranie czcionki do wyswietlenia informacji
	if (!font.loadFromFile("Dane/Font_info.ttf"))
	{
		std::cout << "Nie znaleziono czcionki!" << std::endl;
		return;
	}

	quantity.setFont(font);
	quantity.setCharacterSize(40);

	count = 25;

	quantity.setString(std::to_string(count));
	quantity.setPosition(925 - quantity.getGlobalBounds().width / 2, 438 - quantity.getGlobalBounds().height / 2);

	sprite.setTexture(texture);
	sprite.setPosition(525, 325);
}

Cookie::~Cookie()
{
}

void Cookie::update()
{
	count--;
}

void Cookie::updateText() //uaktualnia napis wyswietlany na ekranie informujacy o ilosci ciasteczek w pudelku
{
	quantity.setString(std::to_string(count));
	quantity.setPosition(925 - quantity.getGlobalBounds().width / 2, 438 - quantity.getGlobalBounds().height / 2);
}

sf::Text &Cookie::getQuantity()
{
	return quantity;
}

int Cookie::getCount()
{
	return count;
}

void Cookie::setCount(int n)
{
	count = n;
}
