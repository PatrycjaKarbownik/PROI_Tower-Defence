//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#pragma once
#include "Tower.h"

class Tower_wmelon : public Tower
{
public:
	Tower_wmelon(sf::Texture &textureWmT, int x, int y);
	~Tower_wmelon();

	void shot(Monster *monster, float time) override;
	void shotMonster(Monster *monster) override;
	bool shot(Monster* monster, std::vector<Path*> path) override;

	virtual void changePrice() override;
	virtual void changeOffence() override;
	virtual void changeSpeed() override;

	virtual void setPrice(int n) override;
	virtual void setOffence(int n) override;
	virtual void setSpeed(int n) override;

	static int price;
	static int speed;
	static int offence;
};