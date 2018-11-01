//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#include "Tower_orange.h"

int Tower_orange::price = 40;
int Tower_orange::offence = 2;
int Tower_orange::speed = 7;

Tower_orange::Tower_orange(sf::Texture &textureOrT, int x, int y)
{
	//pobranie teksturki pocisku pomaranczy
	if (!textureBul.loadFromFile("Dane/Bul_Or.png"))
	{
		std::cout << "Nie znaleziono tekstury pocisku pomaranczy!" << std::endl;
		return;
	}

	type = ORANGE;


	sprite.setTexture(textureOrT);
	sprite.setPosition(x, y);

	range = 150.0f;

	sprite.setOrigin(0.0f, 0.0f);
	show = true;
}

Tower_orange::~Tower_orange()
{
}

bool Tower_orange::shot(Monster* monster, std::vector<Path*> path)
{
	return false;
}

void Tower_orange::changeOffence()
{
	offence += 4;
}

void Tower_orange::changeSpeed()
{
	speed += 3;
}

void Tower_orange::changePrice()
{
	price *= 2;
}

void Tower_orange::setPrice(int n)
{
	price = n;
}

void Tower_orange::setOffence(int n)
{
	offence = n;
}

void Tower_orange::setSpeed(int n)
{
	speed = n;
}

void Tower_orange::shot(Monster *monster, float time)
{
	if (!bul) //sprawdzamy czy w wiezy jest pocisk, zeby dodac go tylko raz
	{
		bullet = new Bullett(textureBul, getPosition().x + getBoundingBox().width / 2, getPosition().y + getBoundingBox().height / 2);
		bul = true; //zmieniamy status pocisku 
	}

	static sf::Vector2f monstPosition;

	monstPosition = monster->getPosition();
	monster->changeShoted(false);

	sf::Vector2f bullPos = bullet->getPosition();; //koordynaty pocisku
    float distance2 = sqrt((bullPos.x - monstPosition.x)*((bullPos.x - monstPosition.x)) + //odleglosc pocisku od potworka
		(bullPos.y - monstPosition.y)*(bullPos.y - monstPosition.y));

	if (distance2 > 1) //jezeli odleglosc od potworka jest wieksza od 1
	{
		bullPos.x += speed * time *(monstPosition.x - bullPos.x) / distance2;
		bullPos.y += speed * time *(monstPosition.y - bullPos.y) / distance2;
		bullet->setPosition(bullPos.x, bullPos.y);
	}
	else
	{
		bullet->setPosition(getPosition().x + getBoundingBox().width / 2, getPosition().y + getBoundingBox().height / 2);
		monsterTrace = false; //teraz pocisk moze pobrac nowe koordynaty potworka i tam strzelic
	}

	shotMonster(monster);
}

void Tower_orange::shotMonster(Monster *monster)
{
	if (bullet->checkCollisionMonster(monster) && !monster->isShoted()) //jesli pocisk trafi w potworka
	{
		monster->changeDelete(false);
		monster->changeShoted(true);
		monster->updateMonster(offence);
	}
}