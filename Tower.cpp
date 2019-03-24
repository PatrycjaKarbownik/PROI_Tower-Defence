//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#include "Tower.h"

Tower::Tower()
{
}

Tower::~Tower()
{
}

bool Tower::showF()
{
	return show;
}

bool Tower::showBul()
{
	return bul;
}

float Tower::getRange()
{
	return range;
}

void Tower::changeBul(bool value)
{
	bul = value;
}

void Tower::changeMegaTow(bool value)
{
	megaTow = value;
}

void Tower::megaRange()
{
	range  = 500;
}

void Tower::changeMonsterTrace(bool value)
{
	monsterTrace = value;
}

void Tower::deleteBullet()
{
	delete bullet;
}

Bullett &Tower::getBullet()
{
	return *bullet;
}

int Tower::getType()
{
	return type;
}

void get() {};

template <class Tower, typename... Smth> void get(Tower* tower, Smth... smth)
{
	tower->megaRange(); //zwieksza sie range stojacych obok wiez
	tower->changeMegaTow(true);
	get(smth...);
};

void Tower::megaTower(std::vector<Tower*> towers)
{
	if (type == 0)
		for (int j = 0; j < towers.size(); j++)
			if ((towers[j]->getType() == 2))
			{
				float distance = sqrt((getPosition().x - towers[j]->getPosition().x)*(getPosition().x - towers[j]->getPosition().x) +
					(getPosition().y - towers[j]->getPosition().y)*(getPosition().y - towers[j]->getPosition().y));
				if (distance <= 50 && !megaTow && !towers[j]->megaTow)
				{
					get(towers[j], this);
				}
			}
}
