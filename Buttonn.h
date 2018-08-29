#pragma once
#include "Texturee.h"
#include "Tower.h"
#include "Tower_apple.h"
#include "Tower_orange.h"
#include "Tower_wmelon.h"
#include "Tower_straw.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Buttonn : public Texturee
{
public:
	enum towerType { APPLE, ORANGE, WMELON, STRAW, APPLEUP, ORANGEUP, WMELONUP, STRAWUP, SAVE };
	towerType type;

	Buttonn(sf::Texture &texture, towerType value, int x, int y);//, int price);
	~Buttonn();

	void updatebutton(sf::RenderWindow &window, int x, int y); //funkcja uaktualniajaca wyglad przycisku

	int getType();
	void changeShape(char color, int x, int y);
	void changeShapeT(bool value);
	void changeClick(bool value);
	void changeUpgrade(bool value);

	int enoughMoney(int towerType, int money);

	void ifPressed(sf::RenderWindow &window);

	bool clickF();
	bool shapeTF();
	bool getUpgrade();

	sf::Vector2f buttonCoord();

	sf::Sprite &getButton();
	sf::RectangleShape &getShape();

private:
	sf::Vector2u butSize;
	sf::RectangleShape shape;

	bool click = false;
	bool shapeT = false;
	bool upgrade = false;
};