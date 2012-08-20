#include "GameMaster.h"

GameMaster::GameMaster(){
	current = NULL;
}

GameMaster::~GameMaster(){
	delete current;
}

void GameMaster::playStep(){
	//TODO if maxNumPoints < LIMIT
	if (!this->isEnded()){  // Game in progress

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
	if(current->isEnded()){
		delete current;
		current = new Point();
	}
	return current;
}

bool GameMaster::isEnded(){
	return false // TODO implement
}