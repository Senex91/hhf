#include "Game.h"

Game::Game() : ogre(*this), ois(*this), map(*this), connection(*this) {
	connection.initialize();
	ogre.initialize();
	ois.initialize();
	map.initialize();
}

Game::~Game() {
	map.destroy();
	ois.destroy();
	ogre.destroy();
}

void Game::run() {
	running = true;
	while(running) {
		connection.update();
		map.update();
		ois.update();
		ogre.update();
	}
	
}
