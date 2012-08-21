#include "Round.h"

Round::Round(){
	physics = NULL;
	initialNumPlayers = physics->numAlivePlayers();

}

Round::~Round(){
}

void Round::playStep(){

	// throws orb if not thrown yet
	if(!physics->isOrbAlive()){
		physics->spawnOrb();
	}

	// spawns felhound if not spawned yet
	if (!physics->isFelhoundAlive()){
		physics->spawnFelhound();
	}

	// game physics
	physics->tick();

	// ON PLAYER DEATH:
	// remove player, give time for client side animation to occur
	// Round::isEnded() = true, 
	// this round will be deconstructed by the Point

}

bool Round::isEnded(){
	if((initialNumPlayers - 1) == physics->numAlivePlayers()){
		// we have one fewer player than we started with.
		// round will be deconstructed.
		return true;
	} else if (initialNumPlayers  == physics->numAlivePlayers()){
		//we have same number of players
		return false;
	}

	// if we reach here there is an error...
	return false;
}