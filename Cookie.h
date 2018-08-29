#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Texturee.h"

class Cookie : public Texturee //pudelko z ciasteczkami
{
public:
	Cookie();
	~Cookie();

	void update(); //uaktualnia napis wyswietlany na ekranie informujacy o ilosci ciasteczek w 
	void updateText();
	sf::Text &getQuantity();
	int getCount();
	void setCount(int n);

private:
	sf::Font font;
	sf::Text quantity;
	int count; //w pudelku tylko ilosc ciasteczek
};