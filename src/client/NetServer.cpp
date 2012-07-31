#include "NetServer.h"

// #include "GameState.h"


NetServer::NetServer():latestState(){
	std::vector<Elf> elves;
    elves.push_back((Elf) {1, 0, 0, 0, 0});
    latestState.elves = elves;
    latestState.felhound = (Felhound) {2, 2, 0, 0};
	
}

NetServer::~NetServer(){

}

GameState const& NetServer::getGameState(){

	return latestState;
}

