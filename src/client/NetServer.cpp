#include "NetServer.h"

// #include "GameState.h"


NetServer::NetServer():latestState(){
	std::vector<Elf> elves;
    elves.push_back((Elf) {0, 0, 0, 0, 0});
    elves.push_back((Elf) {1, 4, 4, 0, 0});
    latestState.elves = elves;
    latestState.felhound = (Felhound) {2, 2, 0, 0};
	
}

NetServer::~NetServer(){

}

GameState const& NetServer::getGameState(){
	latestState.elves[0].y = latestState.elves[0].y + 0.01;
	// latestState.elves[0].x = latestState.elves[0].x + 0.01;

	// latestState.felhound.x = latestState.felhound.x + 1;
	// latestState.felhound.y = latestState.felhound.y + 1;

	return latestState;
}

