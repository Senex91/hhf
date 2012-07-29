#include "Game.h"

Game::Game() : ogre(*this), ois(*this), map(*this), connection(*this) {
	connection.initialize();
	ogre.initialize();
	ois.initialize();
	map.initialize();
	cameraMan = new OgreBites::SdkCameraMan(ogre.getCamera());
	// cameraMan->setStyle(OgreBites::CS_ORBIT);
}

Game::~Game() {
	map.destroy();
	ois.destroy();
	ogre.destroy();
}

void Game::run() {
	running = true;
	while(running) {
		// GameState state = connection.getState();
		connection.update();
		map.update();
		ois.update();
		ogre.update();
	}
	
}
