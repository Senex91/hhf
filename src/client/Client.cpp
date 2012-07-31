#include "Client.h"

#include <cstddef>
#include <SDL.h>

#include "GameState.h"

#include "Debug.h"

Client& Client::getInstance() {
	static Client client; // Only gets instantiated once
	return client;
}

Client::Client(): gameRenderer(), server(), running(false){
	
}

Client::~Client(){
	DEBUG("client destructor called");
}

void Client::run(){
	running = true;
	while(running){
		GameState currentState =  server.getGameState();
		DEBUG(gameStateToString(currentState));
		// gameRenderer.renderNextState(currentState);
		SDL_Delay(1000); // TODO magic number
	}

}