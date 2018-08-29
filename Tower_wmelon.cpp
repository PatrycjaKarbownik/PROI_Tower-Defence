#include "Tower_wmelon.h"

int Tower_wmelon::price = 15;
int Tower_wmelon::offence = 25;
int Tower_wmelon::speed = 10;

Tower_wmelon::Tower_wmelon(sf::Texture &textureWmT, int x, int y)
{
	//pobranie teksturki pocisku arbuza
	if (!textureBul.loadFromFile("Dane/Bul_Wm.png"))
	{
		std::cout << "Nie znaleziono tekstury pocisku arbuza!" << std::endl;
		return;
	}

	type = WMELON;

	sprite.setTexture(textureWmT);
	sprite.setPosition(x, y);

	range = 100.0f;

	sprite.setOrigin(0.0f, 0.0f);
	show = true;
}

Tower_wmelon::~Tower_wmelon()
{
}

bool Tower_wmelon::shot(Monster* monster, std::vector<Path*> path)
{
	return false;
}

void Tower_wmelon::changePrice()
{
	price *= 2;
}

void Tower_wmelon::changeOffence()
{
	offence += 10;
}

void Tower_wmelon::changeSpeed()
{
	speed += 2;
}

void Tower_wmelon::setPrice(int n)
{
	price = n;
}

void Tower_wmelon::setOffence(int n)
{
	offence = n;
}

void Tower_wmelon::setSpeed(int n)
{
	speed = n;
}

void Tower_wmelon::shot(Monster *monster, float time)
{
	if (!bul) //sprawdzamy czy w wiezy jest pocisk, zeby dodac go tylko raz
	{
		bullet = new Bullett(textureBul, getPosition().x + getBoundingBox().width / 2, getPosition().y + getBoundingBox().height / 2);
		bul = true; //zmieniamy status pocisku 
	}
	static sf::Vector2f monstPosition;

	if (!monsterTrace) //warunek zeby pobrac koordynaty potworka tylko raz, i zmienic po strzale
	{
		monstPosition = monster->getPosition();
		monsterTrace = true;
		monster->changeShoted(false);
	}

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

void Tower_wmelon::shotMonster(Monster *monster)
{
	if (bullet->checkCollisionMonster(monster) && !monster->isShoted()) //jesli pocisk trafi w potworka
	{
		monster->changeDelete(false);
		monster->changeShoted(true);
		monster->updateMonster(offence);
	}
}