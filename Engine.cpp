//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#include "Engine.h"
#include "Monster.h"
#include "Tower.h"
#include "Tower_apple.h"
#include <ctime>

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int Engine::pathPoint = 0; //statyczna pozycja sciezki, zaczynamy od zera

class MyException : std::exception
{
public:
	MyException(std::string napis)
	{
		std::cout << napis << std::endl;
	}
};

Engine::Engine(sf::RenderWindow & window)
{
	menu = false;
	try
	{
		downloadTextures();
	}
	catch (MyException)
	{
		menu = true;
	}

	downloadPath();
	downloadStone();
	downloadRiver();
	downloadButtons();
	downloadFonts();

	money = 300;
	monstersCount = 2;
	monstersStrength = 100;

	map.setTexture(teksMap);
	map.setPosition(0, 0);

	deltaTime = 0.0f;
	totalTime = 0.0f;
	switchTime = 0.2f;
}

Engine::Engine(int money, int monsterCount, int monstersStrength, int cookieCount, int towersCount, int aSpeed, int aOffence, int aPrice,
				int oSpeed, int oOffence, int oPrice, int sOffence, int sPrice, int wSpeed, int wOffence, int wPrice, std::vector<int> x,
				std::vector<int> y, std::vector<int> type)
{
	printf("bo ze tutaj, to nie wierze\n");
	menu = false;
	try
	{
		downloadTextures();
	}
	catch (MyException)
	{
		menu = true;
	}

	downloadPath();
	downloadStone();
	downloadRiver();
	downloadButtons();
	downloadFonts();

	printf("a moze tu?\n");

	this->money = money;
	this-> monstersCount = monsterCount;
	this->monstersStrength = monstersStrength;
	cookie.setCount(cookieCount);
	printf("load parametry chyba ok???\n");

	for (int i = 0; i < towersCount; i++)
	{
		printf("tu problem? 1\n");
		if (type[i] == 0)
			towers.push_back(new Tower_apple(textureApT, x[i],y[i]));
		else if (type[i] == 1)
			towers.push_back(new Tower_orange(textureOrT, x[i], y[i]));
		else if (type[i] == 2)
			towers.push_back(new Tower_wmelon(textureWmT, x[i], y[i]));
		else if (type[i] == 3)
			towers.push_back(new Tower_straw(textureStT, x[i], y[i]));
	}

	for(int i=0; i<towersCount; i++) //robie kazde osobno, dlatego, ze to bedzie chyba szybsze dla komputera. moze w petli wyzej powinnam to robic,
		if (towers[i]->getType() == 0)		//ale wtedy kilka razy zapisuje jedna zmienna statyczna. nie wiem czy to bedzie dobre
		{
			printf("tu problem? 2\n");
			towers[i]->setOffence(aOffence);
			towers[i]->setSpeed(aSpeed);
			towers[i]->setPrice(aPrice);
			break;
		}

	for (int i = 0; i<towersCount; i++)
		if (towers[i]->getType() == 1)
		{
			printf("tu problem? 3\n");
			towers[i]->setOffence(oOffence);
			towers[i]->setSpeed(oSpeed);
			towers[i]->setPrice(oPrice);
			break;
		}

	for (int i = 0; i<towersCount; i++)
		if (towers[i]->getType() == 2)
		{
			printf("tu problem? 4\n");
			towers[i]->setOffence(wOffence);
			towers[i]->setSpeed(wSpeed);
			towers[i]->setPrice(wPrice);
			break;
		}

	for (int i = 0; i<towersCount; i++)
		if (towers[i]->getType() == 3)
		{
			printf("tu problem? 5\n");
			towers[i]->setOffence(sOffence);
			towers[i]->setPrice(sPrice);
			break;
		}

	map.setTexture(teksMap);
	map.setPosition(0, 0);

	deltaTime = 0.0f;
	totalTime = 0.0f;
	switchTime = 0.2f;
}

Engine::~Engine() 
{
	monsters.clear();
	towers.clear();
	path.clear();
	stones.clear();
	riv.clear();
//	bullet.clear();
}

int Engine::runEngine(sf::RenderWindow & window)
{
	while (!menu)
	{
		if (cookie.getCount() == 0)
			menu = true;		

		deltaTime = clock.restart().asSeconds();
		time = clock.getElapsedTime().asMicroseconds(); 
		time = time / 100; // Time jest potrzebny do shot

		allForMonsters();
		allForTowers();			
		updatemoney();
		cookie.updateText();
		
		while (window.pollEvent(evnt))
		{
			allForButtons(window);

			switch (evnt.type)
			{
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape || evnt.key.code == sf::Keyboard::Return)
					menu = true;
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		showAll(window);
	}

	return cookie.getCount();
}

void Engine::save(sf::RenderWindow &window, Buttonn& button)
{
	if (button.clickF()) //czy zostal wcisniety przycisk wiezy
	{
		button.changeClick(false);
		
		/*std::ofstream saveFile("Save/save.sav", std::ios::binary);

		Save *file = new Save(money, monstersCount, monstersStrength, cookie.getCount(), towers.size(), Tower_apple::speed, Tower_apple::offence, Tower_apple::price,
			Tower_orange::speed, Tower_orange::offence, Tower_orange::price, Tower_straw::offence, Tower_straw::price,
			Tower_wmelon::speed, Tower_wmelon::offence, Tower_wmelon::price, towers);

		saveFile.write((char*)(file), sizeof(Save));
		printf("sss\n");
		delete file;*/
		std::ofstream saveFile("Save/save.txt");
		saveFile << money << std::endl << monstersCount << std::endl << monstersStrength << std::endl << cookie.getCount() << std::endl
			<< towers.size() << std::endl << Tower_apple::speed << std::endl << Tower_apple::offence << std::endl << Tower_apple::price << std::endl
			<< Tower_orange::speed << std::endl << Tower_orange::offence << std::endl << Tower_orange::price << std::endl
			<< Tower_straw::offence << std::endl << Tower_straw::price << std::endl << Tower_wmelon::speed << std::endl << Tower_wmelon::offence << std::endl
			<< Tower_wmelon::price << std::endl;
		
		if (!towers.empty())
			for (int i = 0; i < towers.size(); i++)
			{
				saveFile << towers[i]->getPosition().x << " " << towers[i]->getPosition().y << " " << towers[i]->getType() << std::endl;
				printf("save\n");
			}
	}
}

void Engine::allForMonsters()
{
	if (!monsters.empty()) //nie przesuwamy potwrokow po sciezce, jezeli nie ma kogo przesuwac
	{	
		monsterMove();
		for (int i = 0; i < monsters.size(); i++)
		{
	//		monsters[i]->monsterMove(monsters, path, deltaTime, i);
			monsters[i]->takeCookie(&cookie);
		}
			
	}
	else //kiedy monsterki znikaja, to dodaja sie nowe
	{
		downloadMonsters(monstersCount, monstersStrength);
		monstersCount += 3;
		monstersStrength += 50;
		pathPoint = 0;
	}
}
void Engine::allForTowers()
{
	if (towers.size() > 0 && !monsters.empty())
	{	
		for (int i = 0; i < towers.size(); i++) 
		{
			towers[i]->megaTower(towers);
			if (monsters.empty()) // bo moga zginac wszystkie potworki
			{
				break;
			}

			if (towers[i]->getType() != 3)  //wszystkie wieze oprocz truskawkowej sprawdzaja czy potworek jest w zasiegu strzalu
			{

				inRange(towers[i], monsters[0]);
			}
			else
				if (towers[i]->shot(monsters[0], path)) //dla truskawkowej wiezy z minami
					killMonster();
		}
	}
}
void Engine::allForButtons(sf::RenderWindow &window)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->ifPressed(window); //przyciski stawiania wiez i upgrade
		if (buttons[i]->getType() < 4) //dla przyciskow stawiania wiez
			standTower(window, *buttons[i]);
		else if (buttons[i]->getType() == 8)
			save(window, *buttons[i]);//save
		else //przyciski upgrade
			upgrade(window, *buttons[i]);
	}
}

void Engine::upgrade(sf::RenderWindow &window, Buttonn& button) //funkcja dzieki ktorej mozna upgrade'owac wieze. 
{
	if (button.clickF()) //czy zostal wcisniety przycisk wiezy
	{
		for (int i = 0; i < towers.size(); i++)
			if (towers[i]->getType() == button.getType() - 4)
			{
				int cost = button.enoughMoney(towers[i]->getType(), money);
				if (cost != 0)
				{
					money -= cost;
					towers[i]->changePrice();
					towers[i]->changeOffence();
					if (towers[i]->getType() != 3)
						towers[i]->changeSpeed();

					break;
				}
			}

		button.changeClick(false);
	}
}

void Engine::standTower(sf::RenderWindow &window, Buttonn& button)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window); //pozycja myszy
	if (button.clickF()) //czy zostal wcisniety przycisk wiezy
		if (checkCollisionTower(window, &button))   //tu sprawdzamy czy koordynaty myszy do stawiania wiezy sa dopuszczalne
		{
			button.changeShapeT(true); //pojawia sie bialy kwadracik
			button.changeShape('w', mousePos.x - (mousePos.x % 25), mousePos.y - (mousePos.y % 25)); //zmiana atrybutow kwadracika, ktory pokazuje dostepnosc miejsca dla wiezy

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				button.changeShapeT(false); //znika bialy kwadracik
				button.changeClick(false);
				if (button.getType() == 0 && money >= Tower_apple::price) //APPLE   
				{
					towers.push_back(new Tower_apple(textureApT, mousePos.x - (mousePos.x % 25), mousePos.y - (mousePos.y % 25))); //tam, gdzie jest mysz powstaje wieza
					money -= Tower_apple::price;
				}
				else if (button.getType() == 1 && money >= Tower_orange::price) //ORANGE
				{
					towers.push_back(new Tower_orange(textureOrT, mousePos.x - (mousePos.x % 25), mousePos.y - (mousePos.y % 25)));
					money -= Tower_orange::price;
				}
				else if (button.getType() == 2 && money >= Tower_wmelon::price) //WMELON
				{
					towers.push_back(new Tower_wmelon(textureWmT, mousePos.x - (mousePos.x % 25), mousePos.y - (mousePos.y % 25)));
					money -= Tower_wmelon::price;
				}
				else if (button.getType() == 3 && money >= Tower_straw::price) //STRAW
				{
					towers.push_back(new Tower_straw(textureStT, mousePos.x - (mousePos.x % 25), mousePos.y - (mousePos.y % 25)));
					money -= Tower_straw::price;
				}
			}
		}
		else if ((mousePos.x < 825) && (mousePos.x > 0) && !checkCollisionTower(window, &button)) //warunek, by mysz byla w obrebie mapy i miejsce dla wiezy bylo niedostepne
		{
			button.changeShapeT(true); //pojawia sie czerwony kwadracik
			button.changeShape('r', mousePos.x - (mousePos.x % 25), mousePos.y - (mousePos.y % 25));
		}
}

bool Engine::checkCollisionTower(sf::RenderWindow &window, Buttonn *button)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::RectangleShape shapeS = button->getShape();
	sf::FloatRect box1(shapeS.getGlobalBounds());
	sf::FloatRect cookie(cookie.getBoundingBox());

	if (box1.intersects(cookie) || mousePos.x < 0 || mousePos.x >= 800 || mousePos.y < 0 || mousePos.y >= 575)// ograniczenie menu i pudelka
		return false;

	for (int i = 0; i < towers.size(); i++)
	{
		sf::FloatRect tower(towers[i]->getBoundingBox());
		if (box1.intersects(tower)) return false;
	}

	for (int i = 0; i < path.size(); i++)
	{
		sf::FloatRect path(path[i]->getBoundingBox());
		if (box1.intersects(path)) return false;
	}

	for (int i = 0; i < stones.size(); i++)
	{
		sf::FloatRect stones(stones[i]->getBoundingBox());
		if (box1.intersects(stones)) return false;
	}

	for (int i = 0; i < riv.size(); i++)
	{
		sf::FloatRect riv(riv[i]->getShape().getGlobalBounds());
		if (box1.intersects(riv)) return false;
	}

	return true;
}

void Engine::inRange(Tower * tower, Monster * monster)
{                                                                                                                                        //zmienilam tu z monster[0] na monster->
	float distance = sqrt((tower->getPosition().x - (monster->getPosition().x))*((tower->getPosition().x - monster->getPosition().x)) +  //bo to lepiej pasuje mi do logiki.
		((tower->getPosition().y - monster->getPosition().y)*(tower->getPosition().y - monster->getPosition().y))); //juz do funkcji dostaje wskaznik na konkretnego potworka,																												//a przy wywolaniu jest podany monsters[0]

	if (distance <= tower->getRange())// && !monsters.empty())
	{
		tower->shot(monster, time);
		killMonster();
	}
	else if (distance > tower->getRange() && tower->showBul() || monsters.empty())
	{
		tower->deleteBullet();
		tower->changeBul(false);
		tower->changeMonsterTrace(false);
	}
}

void Engine::showAll(sf::RenderWindow &window)
{
	window.clear(sf::Color::Black);
	window.draw(map); //mapeczka
	for (int i = 0; i < path.size(); i++)
		window.draw(*path[i]); //sciezka
	for (int i = 0; i < stones.size(); i++)
		window.draw(*stones[i]); //kamienie
	if (!monsters.empty())
		for (int i = 0; i < monsters.size(); i++)
			if (!monsters[i]->deleteMon())
				window.draw(*monsters[i]); //potworki
	window.draw(cookie); //pudelko ciasteczek

	for (int i = 0; i < towers.size(); i++)
	{
		window.draw(*towers[i]); //wieze
		if (towers[i]->showBul())
			window.draw(towers[i]->getBullet()); //pociski
	}

	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->shapeTF())
			window.draw(buttons[i]->getShape()); // dostepnosc pola na wieze - jablko
		window.draw(buttons[i]->getButton()); //przycisk wiezy -jablko
	}

	window.draw(cookie.getQuantity()); //ilosc ciasteczek w pudelku
	window.draw(quantityM); //ilosc monet
	window.draw(priceApple); //koszt jablkowej wiezy
	window.draw(priceOrange); //koszt pomaranczowej wiezy
	window.draw(priceWMelon); //koszt arbuzowej wiezy
	window.draw(priceStraw); //koszt truskawkowej wiezy
	window.draw(priceAppleUp); //koszt upgrade'u jablkowej wiezy
	window.draw(priceOrangeUp); //koszt upgrade'u pomaranczowej wiezy
	window.draw(priceWMelonUp); //koszt upgrade'u arbuzowej wiezy
	window.draw(priceStrawUp); //koszt upgrade'u truskawkowej wiezy

	window.display();
}

void Engine::monsterMove()
{
	int size = path.size();
	int sizeM = monsters.size();
	totalTime += deltaTime;		

	if (totalTime >= switchTime && pathPoint !=size) //ograniczenie j!=size nie jest potrzebne, ale zeby miec pewnosc, ze nie przekrocimy wektor (bo inaczej strasznie krzyczy)
	{
    	totalTime -= switchTime;	
		for (int k = 0; k < sizeM; k++)
			if (pathPoint >= k)
				monsters[k]->setPosition(path[pathPoint - k]->getPosition().x, path[pathPoint - k]->getPosition().y);
		killMonster();	
		pathPoint++;
	}
}

void Engine::killMonster()
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
		delete monsters[0];
		monsters.erase(monsters.begin());
		pathPoint--;
	}
}

void Engine::updatemoney()
{

	quantityM.setString(std::to_string(money));
	quantityM.setPosition(925 - quantityM.getGlobalBounds().width / 2, 513 - quantityM.getGlobalBounds().height / 2);


	priceApple.setString(std::to_string(Tower_apple::price));
	priceApple.setPosition(887 - priceApple.getGlobalBounds().width / 2, 141 - priceApple.getGlobalBounds().height / 2);

	priceOrange.setString(std::to_string(Tower_orange::price));
	priceOrange.setPosition(937 - priceOrange.getGlobalBounds().width / 2, 141 - priceOrange.getGlobalBounds().height / 2);

	priceWMelon.setString(std::to_string(Tower_wmelon::price));
	priceWMelon.setPosition(887 - priceWMelon.getGlobalBounds().width / 2, 191 - priceWMelon.getGlobalBounds().height / 2);

	priceStraw.setString(std::to_string(Tower_straw::price));
	priceStraw.setPosition(937 - priceStraw.getGlobalBounds().width / 2, 191 - priceStraw.getGlobalBounds().height / 2);


	priceAppleUp.setString(std::to_string(Tower_apple::price));
	priceAppleUp.setPosition(887 - priceAppleUp.getGlobalBounds().width / 2, 316 - priceAppleUp.getGlobalBounds().height / 2);

	priceOrangeUp.setString(std::to_string(Tower_orange::price));
	priceOrangeUp.setPosition(937 - priceOrangeUp.getGlobalBounds().width / 2, 316 - priceOrangeUp.getGlobalBounds().height / 2);

	priceWMelonUp.setString(std::to_string(Tower_wmelon::price));
	priceWMelonUp.setPosition(887 - priceWMelonUp.getGlobalBounds().width / 2, 366 - priceWMelonUp.getGlobalBounds().height / 2);

	priceStrawUp.setString(std::to_string(Tower_straw::price));
	priceStrawUp.setPosition(937 - priceStrawUp.getGlobalBounds().width / 2, 366 - priceStrawUp.getGlobalBounds().height / 2);
}

void Engine::downloadPath()
{
	for (int i = 0; i <= 4; i++)
		path.push_back(new Path(texturePath, 75.0, i*25.0));  //down
	for (int i = 0; i <= 7; i++)
		path.push_back(new Path(texturePath, 100.0 + i*25.0, 100.0));  //right
	for (int i = 0; i <= 5; i++)
		path.push_back(new Path(texturePath, 275.0, 125.0 + i*25.0));   //down
	for (int i = 0; i <= 1; i++)
		path.push_back(new Path(texturePath, 250.0 - i*25.0, 250.0)); //left
	for (int i = 0; i <= 1; i++)
		path.push_back(new Path(texturePath, 225.0, 275.0 + i*25.0)); //down
	for (int i = 0; i <= 7; i++)
		path.push_back(new Path(texturePath, 250.0 + i*25.0, 300.0)); //right
	for (int i = 0; i <= 3; i++)
		path.push_back(new Path(texturePath, 425.0, 275.0 - i*25.0)); //up
	for (int i = 0; i <= 3; i++)
		path.push_back(new Path(texturePath, 450.0 + i*25.0, 200.0)); //right
	for (int i = 0; i <= 6; i++)
		path.push_back(new Path(texturePath, 525.0, 225.0 + i*25.0)); //down

	for (int i = 0; i <= 3; i++)
		path.push_back(new Path(texturePath, 550.0 + i*25.0, 350.0)); //right
	for (int i = 0; i <= 1; i++)
		path.push_back(new Path(texturePath, 625.0, 375.0 + i*25.0)); //down
	path.push_back(new Path(texturePath, 650.0, 400.0)); //right
	for (int i = 0; i <= 8; i++)
		path.push_back(new Path(texturePath, 650.0, 400.0 + i*25.0)); //down
}
void Engine::downloadStone()
{
	stones.push_back(new Stone(textureStone, 775, 525));
	for (int i = 0; i < 2; i++)
	{
		stones.push_back(new Stone(textureStone, 525.0 + i * 6 * 25.0, 75.0));
		stones.push_back(new Stone(textureStone, 575.0 + i * 8 * 25.0, 175.0));
		stones.push_back(new Stone(textureStone, 150.0 - i * 3 * 25.0, 125.0 + i * 5 * 25.0));
		stones.push_back(new Stone(textureStone, 450.0 + i * 10 * 25.0, 425.0 - i * 8 * 25.0));
		stones.push_back(new Stone(textureStone, 175.0 + i * 22 * 25.0, 50.0 + i * 13 * 25.0));
	}
	for (int i = 0; i < 3; i++)
	{
		stones.push_back(new Stone(textureStone, 75.0 + i * 10 * 25.0, 500.0));
		stones.push_back(new Stone(textureStone, 25.0 + i * 6 * 25.0, 200.0 + i * 4 * 25.0));
	}
}
void Engine::downloadRiver()
{	
	for (int y = 25, i = 0; y <= 225; y += 50, i++)
		riv.push_back(new River(375-25*i, y));

	for (int y = 350, i = 0; y <= 550; y += 50, i++)
		riv.push_back(new River(200 - 25 * i, y));
}
void Engine::downloadMonsters(int monstersCount, int monstersStrength)
{
	monsters.push_back(new Monster(textMonster, monstersStrength));
	for (int i = 0; i<monstersCount; i++)
		if (monsters[i]->getPosition().y == 0)
			monsters.push_back(new Monster(textMonster, monstersStrength));
}
void Engine::downloadButtons()
{
	buttons.push_back(new Buttonn(textureBA, Buttonn::towerType::APPLE, 875, 100));
	buttons.push_back(new Buttonn(textureBO, Buttonn::towerType::ORANGE, 925, 100));
	buttons.push_back(new Buttonn(textureBW, Buttonn::towerType::WMELON, 875, 150));
	buttons.push_back(new Buttonn(textureBS, Buttonn::towerType::STRAW, 925, 150));

	buttons.push_back(new Buttonn(textureUpBA, Buttonn::towerType::APPLEUP, 875, 275));
	buttons.push_back(new Buttonn(textureUpBO, Buttonn::towerType::ORANGEUP, 925, 275));
	buttons.push_back(new Buttonn(textureUpBW, Buttonn::towerType::WMELONUP, 875, 325));
	buttons.push_back(new Buttonn(textureUpBS, Buttonn::towerType::STRAWUP, 925, 325));

	buttons.push_back(new Buttonn(textureBSave, Buttonn::towerType::SAVE, 1000, 0));
}
void Engine::downloadTextures()
{
	// nowa cudowna mapeczka *_*
	if (!teksMap.loadFromFile("Dane/mapa.png"))
	{
		throw MyException("Nie znaleziono tekstury mapy!");
	}

	//pobranie teksturki potworka
	if (!textMonster.loadFromFile("Dane/Monster2.png"))
	{
		throw MyException("Nie znaleziono tekstury potworka!");
	}

	//pobranie czcionki do wyswietlanych informacji
	if (!font.loadFromFile("Dane/Font_info.ttf"))
	{
		throw MyException("Nie znaleziono czcionki!");
	}

	//pobranie teksturki wiezy jablka
	if (!textureApT.loadFromFile("Dane/Tower_Apple.png"))
	{
		throw MyException("Nie znaleziono tekstury wiezy jablka!");
	}

	//pobranie teksturki wiezy pomaranczy
	if (!textureOrT.loadFromFile("Dane/Tower_Orange.png"))
	{
		throw MyException("Nie znaleziono tekstury wiezy pomaranczy!");
	}

	//pobranie teksturki wiezy arbuza
	if (!textureWmT.loadFromFile("Dane/Tower_Watermelon.png"))
	{
		throw MyException("Nie znaleziono tekstury wiezy arbuza!");
	}

	//pobranie teksturki wiezy truskawki
	if (!textureStT.loadFromFile("Dane/Tower_Strawberry.png"))
	{
		throw MyException("Nie znaleziono tekstury wiezy truskawski!");
	}

	//pobranie teksturki sciezki
	if (!texturePath.loadFromFile("Dane/Path.png"))
	{
		throw MyException("Nie znaleziono tekstury sciezki!");
	}

	//pobranie teksturki kamienia
	if (!textureStone.loadFromFile("Dane/Stone.png"))
	{
		throw MyException("Nie znaleziono tekstury kamienia!");
	}

	//pobranie teksturki przycisku wiezy jablka
	if (!textureBSave.loadFromFile("Dane/disc.png"))
	{
		throw MyException("Nie znaleziono tekstury przycisku save!");
	}

	//pobranie teksturki przycisku wiezy jablka
	if (!textureBA.loadFromFile("Dane/TowerB_Apple.png"))
	{
		throw MyException("Nie znaleziono tekstury przycisku wiezy jablka!");
	}

	//pobranie teksturki przycisku wiezy pomaranczy
	if (!textureBO.loadFromFile("Dane/TowerB_Orange.png"))
	{
		throw MyException("Nie znaleziono tekstury przycisku wiezy pomaranczy!");
	}

	//pobranie teksturki przycisku wiezy arbuza
	if (!textureBW.loadFromFile("Dane/TowerB_Watermelon.png"))
	{
		throw MyException("Nie znaleziono tekstury przycisku wiezy arbuza!");
	}

	//pobranie teksturki przycisku wiezy truskawki
	if (!textureBS.loadFromFile("Dane/TowerB_Strawberry.png"))
	{
		throw MyException("Nie znaleziono tekstury przycisku wiezy truskawski!");
	}

	//pobranie teksturki przycisku upgrade'u wiezy jablka
	if (!textureUpBA.loadFromFile("Dane/TowerB_AppleUP.png"))
	{
		throw MyException("Nie znaleziono tekstury przycisku wiezy jablka!");
	}

	//pobranie teksturki przycisku upgrade'u wiezy pomaranczy
	if (!textureUpBO.loadFromFile("Dane/TowerB_OrangeUP.png"))
	{
		throw MyException("Nie znaleziono tekstury przycisku wiezy pomaranczy!");
	}

	//pobranie teksturki przycisku upgrade'u wiezy arbuza
	if (!textureUpBW.loadFromFile("Dane/TowerB_WatermelonUP.png"))
	{
		throw MyException("Nie znaleziono tekstury przycisku wiezy arbuza!");
	}

	//pobranie teksturki przycisku upgrade'u wiezy truskawki
	if (!textureUpBS.loadFromFile("Dane/TowerB_StrawberryUP.png"))
	{
		throw MyException("Nie znaleziono tekstury przycisku wiezy truskawski!");
	}
}
void Engine::downloadFonts()
{
	quantityM.setFont(font);
	quantityM.setCharacterSize(40);

	priceApple.setFont(font);
	priceOrange.setFont(font);
	priceWMelon.setFont(font);
	priceStraw.setFont(font);

	priceAppleUp.setFont(font);
	priceOrangeUp.setFont(font);
	priceWMelonUp.setFont(font);
	priceStrawUp.setFont(font);

	priceApple.setCharacterSize(12);
	priceOrange.setCharacterSize(12);
	priceWMelon.setCharacterSize(12);
	priceStraw.setCharacterSize(12);

	priceAppleUp.setCharacterSize(12);
	priceOrangeUp.setCharacterSize(12);
	priceWMelonUp.setCharacterSize(12);
	priceStrawUp.setCharacterSize(12);
}