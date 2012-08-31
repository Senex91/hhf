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

	// get current Game
	Game* toPlay = getCurrentGame();

	// play current point
	toPlay->playStep();
	
}

Game* GameMaster::getCurrentGame(){
	if (current == NULL){
		current = new Game(physics);
	} else if(current->isEnded()){
		delete current;
		current = new Game(physics);
	}

	return current;
}
