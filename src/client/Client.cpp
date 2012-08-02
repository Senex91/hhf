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
}

Client::~Client(){
	// DEBUG("client destructor called");
}

void Client::initialize(){
	// Library construct operations
	ogre.initialize();
	ois.initialize();

	// Game objects
	gameRenderer.initialize();



}

void Client::run(){

	ois.addInputListener(this);
	running = true;
	while(running){

		// Library construct operations
		ois.update();
		ogre.update();

		// Renders newest gamestate
		GameState currentState =  server.getGameState();
		gameRenderer.renderNextState(currentState);

		//Sends commands
		


		// SDL_Delay(1000); // TODO magic number
	}

}

// OIS::KeyListener
bool Client::keyPressed( const OIS::KeyEvent &arg ) {
	// Client::getInstance().getCameraMan().injectKeyDown(arg);
	DEBUG("keypressed! " << arg.key);
	return true;
}
bool Client::keyReleased( const OIS::KeyEvent &arg ) {
	if(arg.key == OIS::KC_F12) {
		setRunning(false);
	}
	// Client::getInstance().getCameraMan().injectKeyUp(arg);
	return true;
}
// OIS::MouseListener
bool Client::mouseMoved( const OIS::MouseEvent &arg ) {
	// Client::getInstance().getCameraMan().injectMouseMove(arg);
	// float x = (float)arg.state.X.abs / (float)arg.state.width;
	// float y = (float)arg.state.Y.abs / (float)arg.state.height;
	
	// Ogre::Vector3 pt = Client::getInstance().getOgreManager().rayCast(x,y);
	// Client::getInstance().getConnection().move(pt);
	
	return true;
}
bool Client::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	// Client::getInstance().getCameraMan().injectMouseDown(arg,id);
	return true;
}
bool Client::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	// Client::getInstance().getCameraMan().injectMouseUp(arg, id);
	return true;
}