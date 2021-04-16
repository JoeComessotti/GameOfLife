#include "Game.h"


// Private function
void Game::initVariables() {
	this->window = nullptr;
}

void Game::initWindow() {
	/*
		- Defines the window
	*/
	this->VideoMode.width = this->WIDTH;
	this->VideoMode.height = this->HEIGHT;

	this->window = new sf::RenderWindow(this->VideoMode, "Conway's Game of Life", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(30);
}

void Game::initCells() {
	/*
		- Initializes all of the cells on the screen.
		- All of the cells start off being dead. 
	*/
	for (int i = 0; i < this->ROWS; i++) {
		for (int j = 0; j < this->COLS; j++) {
			float x = i * this->SCALE;
			float y = j * this->SCALE;
			float scale = this->SCALE;
			this->cells[i][j].setPosition(sf::Vector2f(x, y));
			this->cells[i][j].setSize(sf::Vector2f(scale, scale));
			this->cells[i][j].setFillColor(this->dead);
			this->cells[i][j].setOutlineThickness(1.f);
			this->cells[i][j].setOutlineColor(this->outline);
		}
	} 
}

// Constructor / Destructor 
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initCells();
}

Game::~Game() {
	delete this->window;
}

// Accessors
const bool Game::getIsWindowOpen() const {
	/*
		- Returns a boolean value that is true if the window is open, and false if the window is closed.
	*/
	return this->window->isOpen();
}

// Poll events
void Game::pollEvents() {
	/*
		- Checks for user input such as;
			- Closing the window
			- Pressing the space bar to start the simulation
	*/
	while (this->window->pollEvent(this->event)) {
		switch (this->event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape) {
				this->window->close();
				break;
			}
			if (this->event.key.code == sf::Keyboard::Space) {
				this->go = true;
			}
		case sf::Event::MouseButtonPressed:
			int mouseX = sf::Mouse::getPosition(*this->window).x;
			int mouseY = sf::Mouse::getPosition(*this->window).y;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				// Checks each cell to see if it was clicked on
				for (int i = 0; i < this->ROWS; i++) {
					for (int j = 0; j < this->COLS; j++) {
						int posX1 = cells[i][j].getPosition().x - 1;
						int posX2 = cells[i][j].getPosition().x + this->SCALE + 1;
						int posY1 = cells[i][j].getPosition().y - 1;
						int posY2 = cells[i][j].getPosition().y + this->SCALE + 1;

						// Changes the cell to alive if it was clicked on
						if (mouseX > posX1 && mouseX < posX2 && mouseY < posY2 && mouseY > posY1) {
							cells[i][j].setFillColor(this->alive);
						}
					 
					}
				}
			}
		}
		
	}
}

int Game::getAdjacentCells(int x, int y) {
	/*
		- Returns the number adjacent cells that are alive.
	*/
	int AdjacentCells = 0;
	if (cells[x - 1][y - 1].getFillColor() == this->alive) {
		AdjacentCells += 1;
	}
	if (cells[x][y - 1].getFillColor() == this->alive) {
		AdjacentCells += 1;
	}
	if (cells[x + 1][y - 1].getFillColor() == this->alive) {
		AdjacentCells += 1;
	}
	if (cells[x + 1][y].getFillColor() == this->alive) {
		AdjacentCells += 1;
	}
	if (cells[x + 1][y + 1].getFillColor() == this->alive) {
		AdjacentCells += 1;
	}
	if (cells[x][y + 1].getFillColor() == this->alive) {
		AdjacentCells += 1;
	}
	if (cells[x - 1][y + 1].getFillColor() == this->alive) {
		AdjacentCells += 1;
	}
	if (cells[x - 1][y].getFillColor() == this->alive) {
		AdjacentCells += 1;
	}
	return AdjacentCells;
}

void Game::update() {
	this->pollEvents();
	if (this->go) {
		for (int i = 0; i < this->ROWS; i++) {
			for (int j = 0; j < this->COLS; j++) {
				/*
					- The Rules: 
						- If a cell has less than two adjacent cells, it dies
						- If a cell has more than 3 adjacent cells, it dies
						- If a dead cell has exactly 3 neighbors, it comes to life
						- If an alive cell has 2 or 3 neighbors, it lives onto the next generation

				*/

				if (this->getAdjacentCells(i, j) < 2) {
					cells[i][j].setFillColor(this->dead);
				}
				if (this->getAdjacentCells(i, j) > 3) {
					cells[i][j].setFillColor(this->dead);
				}

				if (this->getAdjacentCells(i, j) == 3) {
					cells[i][j].setFillColor(this->alive);
				}
				
			}
		}
	}
}

void Game::render() {
	this->window->clear();
	/*
		- Draws all of the cells
	*/
	for (int i = 0; i < this->ROWS; i++) {
		for (int j = 0; j < this->COLS; j++) {
			this->window->draw(this->cells[i][j]);
		}
	}

	this->window->display();
}
