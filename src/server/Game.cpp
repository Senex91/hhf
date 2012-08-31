#include "Game.h"

#include <vector>

Game::Game(GamePhysics* phys){
	physics = phys;
	current = NULL;
}

Game::~Game(){
	delete current;
}

void Game::playStep(){
	//TODO if maxNumPoints < LIMIT
	if (physics->getMaxPlayerPoints() > 20){  // Game in progress

		// get current Point
		Point* toPlay = getCurrentPoint();

		// play current point
		toPlay->playStep();

	} else { // Game over

		// Game::isEnded() = true, 
		// this game will be deconstructed by the server.
	}
	
}

Point* Game::getCurrentPoint(){
	if (current == NULL){
		current = new Point(physics);
	} else if(current->isEnded()){
		delete current;
		current = new Point(physics);
	}

	return current;
}
