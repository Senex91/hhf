#include "Round.h"

Round::Round(){

}

Round::~Round(){
	
}

void Round::playStep(){
	// throws orb if not thrown yet
	if(!physics->isOrbAlive()){
	}

	// spawns felhound if not spawned yet
	if (!physics->isFelhoundAlive()){
	}

	// game physics
	physics->tick();

	// ON PLAYER DEATH:
	// remove player, give time for client side animation to occur

}