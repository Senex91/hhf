#include "Point.h"

Point::Point(GamePhysics* phys) {
	physics = phys;
	current = NULL;
	playersSpawned = false;
}

Point::~Point(){
	delete current;
}

void Point::playStep(){

	//TODO consider a switch statement here

	// Spawn players if not spawned yet
	if (!playersSpawned){
		spawnPlayers();
	} else if (!this->isEnded()){ //Normal mode, play game

		Round* toPlay = getCurrentRound();
		toPlay->playStep();

	} else { // 1 player left:

		//unspawn final player

		

		// Point::isEnded() = true, 
		// this point will be deconstructed by the GM
	}


}

Round* Point::getCurrentRound(){

	if (current == NULL){
		current = new Round(physics);
	} else if(current->isEnded()){
		delete current;
		current = new Round(physics);
	}

	return current;
}

void Point::spawnPlayers(){
	// TODO should we wait some time before setting?
	playersSpawned = true;

	//spawn only dead and unspawned playerss
	physics->spawnPlayers();

}

bool Point::isEnded(){
	return !(physics->getNumAlivePlayers() > 1); 
}