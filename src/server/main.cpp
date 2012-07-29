#include <iostream>

#include <ClientConnection.h>
#include "SDL_net.h"
#include "vector"
#include "GameState.h"
#include "iostream"
#include "NetworkConstants.h"
#include "Debug.h"

using std::cout;
using std::endl;

int main() {
	cout << "TODO: write server" << endl;

	// std::vector<Elf> elves;
	// elves.push_back((Elf) {1, 0, 0});
	// elves.push_back((Elf) {2, 0, 1});
	// elves.push_back((Elf) {3, 1, 0});
	// GameState state1;
	// state1.elves = elves;
	// state1.felhound = (Felhound) {2,2};

	// std::string serialized = serializeGameState(state1);

	// GameState state2;
	// state2 = deserializeGameState(serialized);


	// std::cout << gameStateToString(state1) << std::endl;
	// std::cout << serialized << std::endl;
	// std::cout << gameStateToString(state2) << std::endl;

	IPaddress address;
	SDLNet_ResolveHost(&address, "127.0.0.1", 2000);

	ClientConnection connection(address);

	// GameState state;
	std::vector<Elf> elves;
	elves.push_back((Elf) {1, 0, 0});
	elves.push_back((Elf) {2, 0, 1});
	elves.push_back((Elf) {3, 1, 0});
	GameState state1;
	state1.elves = elves;
	state1.felhound = (Felhound) {2,2};

	bool running = true;
	while(running){
		connection.sendGameState(state1);
		DEBUG("Sending state");
		DEBUG(gameStateToString(state1));
		SDL_Delay(1000);
	}

	return 0;

}
