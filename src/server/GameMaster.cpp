#include "GameMaster.h"

GameMaster::GameMaster(){

}

GameMaster::~GameMaster(){
	
}

void GameMaster::playStep(){
	//TODO if maxNumPoints < LIMIT
	if (true){  // Game in progress

		// get current Point
		Point* current = getCurrentPoint(); 

		// play current point
		current->playStep();

	} else { // Game over
		// signal end

	}
	
}

Point* GameMaster::getCurrentPoint(){

	Point p;
	return &p;

}