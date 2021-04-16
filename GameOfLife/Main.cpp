#include "Game.h";

Game game;

int main() {
	
	while (game.getIsWindowOpen()) {
		game.update();
		game.render();
	}
	return 0;
}