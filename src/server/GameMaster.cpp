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

	std::vector<Elf> elves = physics->getGameState().elves;
	for(unsigned int i = 0; i<elves.size(); i++){
		Elf e = elves[i];
		if (e.alive){

			// TODO add elf score field
			if (e.x > maxPoints){
				maxPoints = e.x;
			}
		}
	}

	if (maxPoints < 0){
		//error...
	}

	return maxPoints >= 20; // TODO LIMIT constant
}