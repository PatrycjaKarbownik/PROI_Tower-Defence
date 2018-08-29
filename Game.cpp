#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

Game::Game()
{
	state = END;
	//pobranie czcionki do menu
	if (!font.loadFromFile("Dane/Font_menu.ttf"))
	{
		std::cout << "Nie znaleziono czcionki!" << std::endl;
		return;
	}
	
	//czcionka do rosyjskiego "Game Over"
	if (!rusFont.loadFromFile("Dane/Font_goRus.ttf"))
	{
		std::cout << "Nie znaleziono czcionki!" << std::endl;
		return;
	}
	
	//czcionka do "Game Over"
	if (!goFont.loadFromFile("Dane/Font_go.ttf"))
	{
		std::cout << "Nie znaleziono czcionki!" << std::endl;
		return;
	}

	head.setFont(font);
	head.setCharacterSize(80);
	head.setString("Tower Defence");
	head.setStyle(sf::Text::Bold);
	head.setPosition(1050 / 2 - head.getGlobalBounds().width / 2, 20);

	state = MENU;
}

Game::~Game(void)
{
}

void Game::runGame()
{
	while (state != END)
	{
		sf::RenderWindow appWind(sf::VideoMode(1050, 600, 32), "Tower Defence", sf::Style::Close);
		switch (state)
		{
		case GameState::MENU:
			menu(appWind);
			break;
		case GameState::GAME:
			engine = new Engine(appWind);
			single(appWind);
			break;
		case GameState::LOAD:
			load();
			printf("load tworzy\n");
			engine = new Engine(money, monsterCount, monstersStrength, cookieCount, towersCount, appleSpeed, appleOffence, applePrice,
								orangeSpeed, orangeOffence, orangePrice, strawOffence, strawPrice, wmelonSpeed, wmelonOffence, wmelonPrice,
								x, y, towerType);
			printf("odpali za chwile\n");
			single(appWind);
			break;
		case GameState::GAME_OVER:
			gameOver(appWind);
			break;
		}
	}
}

void Game::menu(sf::RenderWindow &window)
{
	const int amount = 3;
	sf::Text choice[amount];
	std::string str[] = { "Play", "Load Game", "Exit" };

	for (int i = 0; i < amount; i++)
	{
		choice[i].setFont(font);
		choice[i].setCharacterSize(65);
		choice[i].setString(str[i]);
		choice[i].setPosition(1050 / 2 - choice[i].getGlobalBounds().width / 2, 200 + i * 100);
	}

	while (state == MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed || evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Escape)
				state = END;
			else if (choice[2].getGlobalBounds().contains(mouse) && evnt.type == sf::Event::MouseButtonReleased && evnt.key.code == sf::Mouse::Left)
				state = END;
			else if (choice[1].getGlobalBounds().contains(mouse) && evnt.type == sf::Event::MouseButtonReleased && evnt.key.code == sf::Mouse::Left)
				state = LOAD;
			else if (choice[0].getGlobalBounds().contains(mouse) && evnt.type == sf::Event::MouseButtonReleased &&evnt.key.code == sf::Mouse::Left)
				state = GAME;
		}

		for (int i = 0; i < amount; i++)
		{
			if (choice[i].getGlobalBounds().contains(mouse))
				choice[i].setFillColor(sf::Color::Cyan);
			else
				choice[i].setFillColor(sf::Color::White);
		}

		window.clear();
		window.draw(head);
		for (int i = 0; i < amount; i++)
			window.draw(choice[i]);
		window.display();
	}
}

void Game::single(sf::RenderWindow &window)
{
	if (engine->runEngine(window) == 0)
		state = GAME_OVER;
	else
		state = MENU;
	delete engine;
}

void Game::gameOver(sf::RenderWindow & window)
{
	sf::Text txt[3];
	std::string str[3] = { "Exit", "KONEC IGR", "GAME OVER" };
	str[1] += 251;

	txt[0].setFont(font);
	txt[0].setCharacterSize(45);
	txt[0].setString(str[0]);
	txt[0].setPosition(1050 / 2 - txt[0].getGlobalBounds().width / 2, 3*600/4- txt[0].getGlobalBounds().height / 2);

	txt[1].setFont(rusFont);
	txt[1].setCharacterSize(80);
	txt[2].setFont(goFont);
	txt[2].setCharacterSize(50);

	for (int i = 1; i < 3; i++)
	{
		txt[i].setFillColor(sf::Color::Red);
		txt[i].setString(str[i]);
		txt[i].setPosition(1050 / 2 - txt[i].getGlobalBounds().width / 2, 100 + i * 100);
	}

	while (state == GAME_OVER)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed || evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Escape)
				state = END;
			else if (txt[0].getGlobalBounds().contains(mouse) && evnt.type == sf::Event::MouseButtonReleased && evnt.key.code == sf::Mouse::Left)
				state = END;
		}

		if (txt[0].getGlobalBounds().contains(mouse))
			txt[0].setFillColor(sf::Color::Cyan);
		else
			txt[0].setFillColor(sf::Color::White);

		window.clear(sf::Color::Black);
		window.draw(head);
		for(int i=0; i<3; i++)
			window.draw(txt[i]);
		window.display();
	}
}

/*
Save& Game::load()
{
	printf("load wchodzi\n");
	std::ifstream saveFile("Save/save.sav", std::ios::binary);

	char* temp = new char[sizeof(Save)]; // tymczasowy bufor na dane
	saveFile.read(temp, sizeof(Save)); // wczytujemy dane do bufora
	Save* file = (Save*)(temp);
	printf("odczyt?\n");
	return *file;
}
*/

void Game::load()
{
	std::ifstream saveFile("Save/save.txt");

	saveFile >> money >> monsterCount >> monstersStrength >> cookieCount >> towersCount >>
		appleSpeed >> appleOffence >> applePrice >> orangeSpeed >> orangeOffence >> orangePrice >>
		strawOffence >> strawPrice >> wmelonSpeed >> wmelonOffence >> wmelonPrice;

	if (towersCount>0)
		for (int i = 0; i < towersCount; i++)
		{
			int tempx, tempy, temptype;
			saveFile >> tempx >> tempy >> temptype;
			x.push_back(tempx);
			y.push_back(tempy);
			towerType.push_back(temptype);
		}
}