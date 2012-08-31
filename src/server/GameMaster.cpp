#include "GameMaster.h"

#include <vector>

GameMaster::GameMaster(GamePhysics* phys){
	physics = phys;
	current = NULL;
}

GameMaster::~GameMaster(){
	delete current;
}

void GameMaster::playStep(){
	//TODO if maxNumPoints < LIMIT
	if (physics->getMaxPlayerPoints() > 20){  // Game in progress

		// get current Point
		Point* toPlay = getCurrentPoint();

		// play current point
		toPlay->playStep();

	} else { // Game over

		// GameMaster::isEnded() = true, 
		// this game will be deconstructed by the server.
	}
	
}

Point* GameMaster::getCurrentPoint(){
	if (current == NULL){
		current = new Point(physics);
	} else if(current->isEnded()){
		delete current;
		current = new Point(physics);
	}

	return current;
}
