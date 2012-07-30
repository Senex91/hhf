#include "Game.h"

Game::Game() : /*ogre(*this), ois(*this),*/ map(), connection(), running(false) {
	connection.initialize();
	// ogre.initialize();
	// ois.initialize();
	map.initialize();
	// cameraMan = new OgreBites::SdkCameraMan(ogre.getCamera());
	// cameraMan->setStyle(OgreBites::CS_ORBIT);
}

Game::~Game() {
	map.destroy();
	// ois.destroy();
	// ogre.destroy();
}

void Game::run() {
	running = true;
	while(running) {
		map.update();
		connection.update(map);
		//map.update();

		// GameState state = connection.getGameState();
		// map.set
		// ois.update();
		// ogre.update();
	}
	
}
