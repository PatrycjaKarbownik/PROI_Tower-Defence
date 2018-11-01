//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Texturee.h"
#include "Cookie.h"
#include "Path.h"

class Monster : public Texturee
{
public:
	Monster(sf::Texture& teksture, int strength);
	~Monster();

	void changeCookie(bool value);
	void changeShoted(bool value);
	void changeDelete(bool value);
	void takeCookie(Cookie *cookie);
	int changeStrength(int value);
	void monsterMove(std::vector<Monster*> monsters, std::vector<Path*> path, float deltatime, int k);
	void killMonster(std::vector<Monster*> monsters, int money);
	bool isCookieF();
	void updateMonster(int value);
	bool isShoted();
	int getStrength();
	bool deleteMon();
	
private:
	float switchTime;
	float totalTime;
	int pathP;

	int strength;
	bool isCookie;
	bool shoted = false;
	bool deleteMonster = false;
};