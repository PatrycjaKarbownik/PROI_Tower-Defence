//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Tower.h"

class Save
{
public:
	Save(/*int money, int monsterCount, int monstersStrength, int cookieCount, unsigned int towersCount, int aSpeed, int aOffence, int aPrice,
		int oSpeed, int oOffence, int oPrice, int sOffence, int sPrice, int wSpeed, int wOffence, int wPrice, std::vector<Tower*> towers*/);
	~Save();

	/*int getMoney();
	int getMonsterCount();
	int getMonstersStrength();
	int getCookieCount();
	int getTowersCount();
	int getAppleSpeed();
	int getAppleOffence();
	int getApplePrice();
	int getOrangeSpeed();
	int getOrangeOffence();
	int getOrangePrice();
	int getStrawOffence();
	int getStrawPrice();
	int getWmelonSpeed();
	int getWmelonOffence();
	int getWmelonPrice();
	std::vector<int> &getTowerX();
	std::vector<int> &getTowerY();
	std::vector<int> &getTowerType();*/

protected:
	int money;
	int monsterCount;
	int monstersStrength;
	int cookieCount;
	int towersCount;

	int appleSpeed;
	int appleOffence;
	int applePrice;

	int orangeSpeed;
	int orangeOffence;
	int orangePrice;

	int strawOffence;
	int strawPrice;

	int wmelonSpeed;
	int wmelonOffence;
	int wmelonPrice;

	std::vector<int> x;
	std::vector<int> y;
	std::vector<int> towerType;
};

