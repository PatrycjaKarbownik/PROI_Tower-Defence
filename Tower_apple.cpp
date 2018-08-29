#include "Tower_apple.h"

int Tower_apple::price = 30;
int Tower_apple::offence = 50;
int Tower_apple::speed = 15;

Tower_apple::Tower_apple(sf::Texture &textureApT, int x, int y)
{
	//pobranie teksturki pocisku jablka
	if (!textureBul.loadFromFile("Dane/Bul_Ap.png")) //teksturke przemieszczylam tu, zeby funkcja shot byla uniwersalna, zeby nie trzeba bylo pobierac za kazdym razem teksturke pocisku okreslonej wiezy
	{
		std::cout << "Nie znaleziono tekstury pocisku jablka!" << std::endl;
		return;
	}

	type = APPLE;

	sprite.setTexture(textureApT);
	sprite.setPosition(x, y);

	range = 200.0f;

	sprite.setOrigin(0.0f, 0.0f);
	show = true;
}

Tower_apple::~Tower_apple()
{
}

bool Tower_apple::shot(Monster* monster, std::vector<Path*> path)
{
	return false;
}

void Tower_apple::changePrice()
{
	price *= 2;
}

void Tower_apple::changeOffence()
{
	offence += 5;
}

void Tower_apple::changeSpeed()
{
	speed += 5;
}

void Tower_apple::setPrice(int n)
{
	price = n;
}

void Tower_apple::setOffence(int n)
{
	offence = n;
}

void Tower_apple::setSpeed(int n)
{
	speed = n;
}

void Tower_apple::shot(Monster *monster, float time)
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

void Tower_apple::shotMonster(Monster *monster)
{
	if (bullet->checkCollisionMonster(monster) && !monster->isShoted()) //jesli pocisk trafi w potworka
	{
		monster->changeDelete(false);
		monster->changeShoted(true);
		monster->updateMonster(offence);
	}
}