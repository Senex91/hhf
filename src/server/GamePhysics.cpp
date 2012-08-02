#include "GamePhysics.h"

GamePhysics::GamePhysics() {
	state.felhound = (Felhound){0, 0, 0, 0};
	
}

GamePhysics::~GamePhysics() {
	
}

void GamePhysics::tick() {
	
}

void GamePhysics::addPlayer(int id) {
	Elf e = { id, 0, 0, 0, 0};
	state.elves.push_back(e);
}