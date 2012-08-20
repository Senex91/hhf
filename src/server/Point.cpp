#include "Point.h"

Point::Point(): playersSpawned(false) {

}

Point::~Point(){
	
}

void Point::playStep(){

	//TODO consider a switch statement here

	// Spawn players if not spawned yet
	if (!playersSpawned){
		spawnPlayers();
	} else if (physics->numAlivePlayers() > 1){ //Normal mode, play game

		Round* current = getCurrentRound();
		current->playStep();

	} else { // 1 player left:

		// point end sequence
	}


}

Round* Point::getCurrentRound(){

	Round r;
	return &r;
}

void Point::spawnPlayers(){

	//called once playerSpawn is complete
	playersSpawned = true;

}