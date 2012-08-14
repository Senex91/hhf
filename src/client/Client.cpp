#include "Client.h"
#include <cstddef>
#include <SDL.h>
#include "GameState.h"
#include "Debug.h"

Client& Client::getInstance() {
	static Client client; // Only gets instantiated once
	return client;
}

Client::Client(): ogre(), ois(), gameRenderer(), server(), commander(server), running(false){
}

Client::~Client(){
	// DEBUG("client destructor called");
}

void Client::initialize(){
	// Library construct operations
	ogre.initialize();
	ois.initialize();
	cegui.initialize();

	// Game objects
	gameRenderer.initialize();
	


}

void Client::destroy() {
	server.quitServer();
	gameRenderer.destroy();
	ois.destroy();
	ogre.destroy();
}

void Client::run(){

	ois.addMouseListener(this);
	ois.addKeyListener(this);
	ois.addMouseListener(&commander);
	running = true;
	while(running){

		// Library construct operations
		ois.update();
		ogre.update();
		server.receiveData();

		// Renders newest gamestate
		GameState currentState =  server.getGameState();
		gameRenderer.renderNextState(currentState);
		SDL_Delay(1);
	}

}

// OIS::KeyListener
bool Client::keyPressed( const OIS::KeyEvent &arg ) {
	return true;
}
bool Client::keyReleased( const OIS::KeyEvent &arg ) {
	if(arg.key == OIS::KC_F12) {
		setRunning(false);
	}
	return true;
}
// OIS::MouseListener
bool Client::mouseMoved( const OIS::MouseEvent &arg ) {
	return true;
}
bool Client::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return true;
}
bool Client::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return true;
}