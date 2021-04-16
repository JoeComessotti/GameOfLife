#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Game
{
private:
	// Variables
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode VideoMode;
	const int WIDTH = 500;
	const int HEIGHT = 500;
	const int SCALE = 10;
	const int ROWS = 50;
	const int COLS = 50;
	bool go = false;
	sf::RectangleShape cells[50][50];
	sf::Color alive = sf::Color::White;
	sf::Color dead = sf::Color::Black;
	sf::Color outline = sf::Color(128, 128, 128);

	// Private functions
	void initVariables();
	void initWindow();
	void initCells();

public:
	// Constructor / Destructor
	Game();
	virtual ~Game();

	// Accessors 
	const bool getIsWindowOpen() const;

	// Functions
	void pollEvents();
	int getAdjacentCells(int x, int y);
	void update();
	void render();
};

