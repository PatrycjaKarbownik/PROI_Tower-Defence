//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#include "Tower_straw.h"

int Tower_straw::price = 60;
int Tower_straw::offence = 200;


Tower_straw::Tower_straw(sf::Texture &textureStT, int x, int y)
{
	//pobranie teksturki pocisku truskawki
	if (!textureBul.loadFromFile("Dane/Bul_St.png"))
	{
		std::cout << "Nie znaleziono tekstury pocisku truskawki!" << std::endl;
		return;
	}

	type = STRAW;


	sprite.setTexture(textureStT);
	sprite.setPosition(x, y);

	sprite.setOrigin(0.0f, 0.0f);
	show = true;
}

Tower_straw::~Tower_straw()
{
}

void Tower_straw::shot(Monster *monster, float time)
{
}

bool Tower_straw::shot(Monster* monster, std::vector<Path*> path)
{
	if (!bul) //sprawdzamy czy w wiezy jest pocisk, zeby dodac go tylko raz
	{
		sf::Vector2f position;
		bool place = false; //zmienna, ktora mowi czy znalazlo sie juz miejsce na mine
		do
		{
			position = los();

			for (int i = 0; i < path.size(); i++)
				if (position.x == path[i]->getPosition().x && position.y == path[i]->getPosition().y)
				{
					place = true;
					break;
				}
			if (position.x >= 525 && position.x < 575 && position.y >= 325 && position.y < 400)
				place = false;
		} while (!place);

		bullet = new Bullett(textureBul, position.x + 5, position.y + 5); //z tymi piatkami ladniej wyglada :D
		bul = true; //zmieniamy status pocisku 
	}

	if (bullet->explosion(monster, offence))
	{
		bul = false;
		monster->changeShoted(false);
		if (monster->getStrength() == 0)
		{
			return true;
		}
	}
	return false;
}

sf::Vector2f Tower_straw::los()
{
	sf::Vector2f minePosition;

	int x, y;
	x = (((double)rand() / RAND_MAX) * 600) + 75;
	y = ((double)rand() / RAND_MAX) * 600;

	x -= x % 25;
	y -= x % 25;

	minePosition.x = x;
	minePosition.y = y;

	return minePosition;
}

void Tower_straw::shotMonster(Monster *monster)
{
}

void Tower_straw::changePrice()
{
	price *= 2;
}

void Tower_straw::changeOffence()
{
	offence += 15;
}

void Tower_straw::changeSpeed()
{
}

void Tower_straw::setPrice(int n)
{
	price = n;
}

void Tower_straw::setOffence(int n)
{
	offence = n;
}

void Tower_straw::setSpeed(int n)
{
}
