//Autorzy:
//Patrycja Karbownik
//Anna Yelkina

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Monster.h"
#include "Tower.h"
#include "Tower_apple.h"
#include "Tower_orange.h"
#include "Tower_wmelon.h"
#include "Tower_straw.h"
#include "Buttonn.h"
#include "Bullett.h"
#include "Path.h"
#include "Stone.h"
#include "River.h"
#include "Save.h"

class Engine
{
public:
	Engine(sf::RenderWindow &window);
	Engine::Engine(int money, int monsterCount, int monstersStrength, int cookieCount, int towersCount, int aSpeed, int aOffence, int aPrice,
		int oSpeed, int oOffence, int oPrice, int sOffence, int sPrice, int wSpeed, int wOffence, int wPrice, std::vector<int> x, std::vector<int> y, std::vector<int> type);
	~Engine(void);

	int runEngine(sf::RenderWindow &window);
	void save(sf::RenderWindow &window, Buttonn& button);

	//downloads
	void downloadPath();
	void downloadStone();
	void downloadRiver();
	void downloadButtons();
	void downloadTextures();
	void downloadMonsters(int monstersCount, int strength);
	void downloadFonts();
	//monsters
	void monsterMove();
	void killMonster();

	void showAll(sf::RenderWindow &window); //wyswietlenie wszystkich obiektow
	void updatemoney(); //uaktualnia napis wyswietlany na ekranie informujacy o ilosci monet

	void standTower(sf::RenderWindow &window, Buttonn& button);
	bool checkCollisionTower(sf::RenderWindow &window, Buttonn *button);
	void inRange(Tower* tower, Monster *monster);
	void upgrade(sf::RenderWindow &window, Buttonn& button);
	

	void allForMonsters();
	void allForTowers();
	void allForButtons(sf::RenderWindow &window);
	static int pathPoint;
private:
	sf::Sprite map;
	sf::Texture teksMap;
	bool menu;

	sf::Event evnt;
	sf::Texture textMonster;
	sf::Texture textureApT;
	sf::Texture textureOrT;
	sf::Texture textureWmT;
	sf::Texture textureStT;

	sf::Texture textureBSave; //tekstura przycisku - save
	sf::Texture textureBA; //tekstura przycisku - wieza jablko
	sf::Texture textureBO; //tekstura przycisku - wieza pomarancza
	sf::Texture textureBW; //tekstura przycisku - wieza arbuz
	sf::Texture textureBS; //tekstura przycisku - wieza truskawka
	sf::Texture textureUpBA; //tekstura przycisku - upgrade wiezy - jablko
	sf::Texture textureUpBO; //tekstura przycisku - upgrade wiezy - pomarancza
	sf::Texture textureUpBW; //tekstura przycisku - upgrade wiezy - arbuz
	sf::Texture textureUpBS; //tekstura przycisku - upgrade wiezy - truskawka

	sf::Texture texturePath;
	sf::Texture textureStone;

	sf::Clock clock;
	float deltaTime;
	float switchTime;
	float totalTime;
	float time;

	sf::Font font;
	sf::Text quantityM;
	sf::Text priceApple;
	sf::Text priceOrange;
	sf::Text priceWMelon;
	sf::Text priceStraw;
	sf::Text priceAppleUp;
	sf::Text priceOrangeUp;
	sf::Text priceWMelonUp;
	sf::Text priceStrawUp;

	int money;
	int monstersCount;
	int monstersStrength;
	
	Cookie cookie;
	std::vector<Monster*> monsters;
	std::vector<Tower*> towers;
	std::vector<Buttonn*> buttons;
	std::vector<Path*> path;
	std::vector<Stone*> stones;
	std::vector<River*> riv;
};

