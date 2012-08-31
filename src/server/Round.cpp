#include "Round.h"

Round::Round(GamePhysics* phys){
	physics = phys;
	initialNumPlayers = physics->getNumAlivePlayers();

}

Round::~Round(){
}

void Round::playStep(){

	// throws orb if not thrown yet
	if(!physics->isOrbSpawned()){
		physics->spawnOrb();
	}

	// spawns felhound if not spawned yet
	if (!physics->isFelhoundSpawned()){
		physics->spawnFelhound();
	}

	if (!physics->isFelhoundResting()){
		physics->agroFelhound();
	}

	// game physics
	physics->tick();

	// ON PLAYER DEATH:
	//TODO who kills the player...?
	// remove player, give time for client side animation to occur
	// Round::isEnded() = true, 
	// this round will be deconstructed by the Points

}

bool Round::isEnded(){
	if((initialNumPlayers - 1) == physics->getNumAlivePlayers()){
		// we have one fewer player than we started with.
		// round will be deconstructed.
		return true;
	} else if (initialNumPlayers  == physics->getNumAlivePlayers()){
		//we have same number of players
		return false;
	}

	// if we reach here there is an error...
	return false;
}