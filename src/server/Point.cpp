#include "Point.h"
#include "Debug.h"

Point::Point(GamePhysics* phys) {
	physics = phys;
	current = NULL;
}

Point::~Point(){
	delete current;
}

void Point::playStep(){

	//TODO consider a switch statement here

	// Spawn players if not spawned yet
	if (!physics->arePlayersSpawned()){
		physics->spawnPlayers();
	} else if (!this->isEnded()){ //Normal mode, play game

		Round* toPlay = getCurrentRound();
		toPlay->playStep();

	} else { // 1 player left: unspawn final player

		//TODO throw error if numAlivePlayers != 1;
		if(physics->getAlivePlayers().size() != 1){
			DEBUG("ERROR: NOT 1 PLAYER LEFT AT POINT END");
		}
		int finalID = physics->getAlivePlayers()[0];
		//unspawn worthless human
		std::vector<int> unspawnList;
		unspawnList.push_back(finalID);
		physics->unSpawnPlayers(unspawnList);

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

bool Point::isEnded(){
	return !(physics->getNumAlivePlayers() > 1); 
}