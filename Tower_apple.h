#pragma once
#include "Tower.h"

class Tower_apple : public Tower
{
public:
	Tower_apple::Tower_apple(sf::Texture &textureApT, int x, int y);
	~Tower_apple();

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