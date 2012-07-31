#include "Client.h"

#include <cstddef>
#include <SDL.h>

#include "GameState.h"

#include "Debug.h"

Client& Client::getInstance() {
	static Client client; // Only gets instantiated once
	return client;
}

Client::Client(): ogre(), ois(), gameRenderer(), server(), running(false){
	ogre.initialize();
	ois.initialize();
	cameraMan = new OgreBites::SdkCameraMan(ogre.getCamera());
}

Client::~Client(){
	// DEBUG("client destructor called");
}

void Client::run(){
	running = true;
	while(running){

		// Library construct operations
		ogre.update();
		ois.update();

		// Game operations
		GameState currentState =  server.getGameState();
		gameRenderer.renderNextState(currentState);
		SDL_Delay(1000); // TODO magic number
	}

}