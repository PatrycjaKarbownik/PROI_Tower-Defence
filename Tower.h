//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Texturee.h"
#include "Monster.h"
#include "Bullett.h"

class Tower : public Texturee
{
public:
	Tower();
	~Tower();

	enum towerType { APPLE, ORANGE, WMELON, STRAW };
	towerType type;

	bool showF();
	bool showBul();
	float getRange();
	void changeMonsterTrace(bool value);
	void changeBul(bool value);
	void changeMegaTow(bool value);
	void megaRange();
	void deleteBullet();
	int getType();
	
	virtual void changePrice() = 0;
	virtual void changeOffence() = 0;
	virtual void changeSpeed() = 0;

	virtual void setPrice(int n) = 0;
	virtual void setOffence(int n) = 0;
	virtual void setSpeed(int n) = 0;

	void megaTower(std::vector<Tower*> towers);

	Bullett &getBullet();
	
	virtual void shot(Monster *monster, float time) = 0;
	virtual void shotMonster(Monster *monster) = 0;
	virtual bool shot(Monster* monster, std::vector<Path*> path) = 0;

	sf::Texture textureBul; //tekstura pocisku PUBLICZNA?????

protected:

	float range;
	static int speed;
	static int offence;
	static int price;

	bool bul = false;
	bool monsterTrace = false;
	bool megaTow = false; 

	Bullett *bullet;
};