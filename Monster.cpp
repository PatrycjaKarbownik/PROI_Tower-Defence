#include "Monster.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

Monster::Monster(sf::Texture& texture, int strength)
{
	this->strength = strength;
	isCookie = false;

	sprite.setTexture(texture);
	sprite.setPosition(75, 0);
	sprite.setScale(0.2, 0.2);
	sprite.setOrigin(0.1, 0.1);

	totalTime = 0.0f;
	switchTime = 0.2f;
}

Monster::~Monster()
{
}

void Monster::changeCookie(bool value)
{
	isCookie = value;
}

void Monster::changeShoted(bool value)
{
	shoted = value;
}

void Monster::changeDelete(bool value)
{
	deleteMonster = value;
}

bool Monster::isCookieF()
{
	return isCookie;
}

bool Monster::deleteMon()
{
	return deleteMonster;
}

bool Monster::isShoted()
{
	return shoted;
}

int Monster::getStrength()
{
	return strength;
}

int Monster::changeStrength(int value)
{
	return strength = value;
}

void Monster::updateMonster(int offence)
{
	strength -= offence;
}

void Monster::takeCookie(Cookie *cookie) //jak wchodzi do pudelka bierze jedno ciasteczko
{
	if (getPosition().y == 325 && getPosition().x == 525 && !isCookie)
	{
		cookie->update(); //ciasteczko zostalo zabrane przez potworka
		
		isCookie=true; //potworek wzial ciasteczko
	}
}
void Monster::monsterMove(std::vector<Monster*> monsters, std::vector<Path*> path, float deltatime, int k)
{
	int size = path.size();
	totalTime += deltatime;

	if (totalTime >= switchTime && pathP != size) //ograniczenie j!=size nie jest potrzebne, ale zeby miec pewnosc, ze nie przekrocimy wektor (bo inaczej strasznie krzyczy)
	{
		totalTime -= switchTime;
		setPosition(path[pathP - k]->getPosition().x, path[pathP - k]->getPosition().y);
		pathP++;
	}
	if (getPosition().y == 600)
	{
		monsters.erase(monsters.begin());
		pathP = 0;
	}
	k++;
}

void Monster::killMonster(std::vector<Monster*> monsters, int money)
{
	if (monsters[0]->getStrength() <= 0 && !monsters[0]->deleteMon())
	{
	//	printf("ZABIC \n");
		monsters[0]->changeDelete(true);
		delete monsters[0];
		monsters.erase(monsters.begin());
		money += 50;
	}
	else if (monsters[0]->getPosition().y == 600)
	{
		monsters.erase(monsters.begin());
//		pathPoint--;
	}
}


