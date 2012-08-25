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
	if (current == NULL){
		current = new Point(physics);
	} else if(current->isEnded()){
		delete current;
		current = new Point(physics);
	}

	return current;
}

bool GameMaster::isEnded(){

	int maxPoints = -1;

	std::map<int, Elf> elves = physics->getGameState().elves;

	typedef std::map<int, Elf>::const_iterator it_type;
	for(it_type iterator = elves.begin(); iterator != elves.end(); iterator++) {
		// Elf e = elves[i];
		if (iterator->second.alive){

			// TODO add elf score field
			if (iterator->second.x > maxPoints){
				maxPoints = iterator->second.x;
			}
		}
	}

	if (maxPoints < 0){
		//error...
	}

	return maxPoints >= 20; // TODO LIMIT constant
}