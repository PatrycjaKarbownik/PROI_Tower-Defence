#pragma once
#include "Tower.h"

class Tower_straw : public Tower
{
public:
	Tower_straw(sf::Texture &textureStT, int x, int y);
	~Tower_straw();

	bool shot(Monster* monster, std::vector<Path*> path) override;
	void shot(Monster *monster, float time) override;
	void shotMonster(Monster *monster) override;
	sf::Vector2f los();

	virtual void changePrice() override;
	virtual void changeOffence() override;
	virtual void changeSpeed() override;

	virtual void setPrice(int n) override;
	virtual void setOffence(int n) override;
	virtual void setSpeed(int n) override;

	static int price;
	static int offence;
};