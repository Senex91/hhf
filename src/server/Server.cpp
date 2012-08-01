#include "Server.h"
#include <cstdlib>
#include <cstdio>
#include "Debug.h"

Server::Server(): socket(SERVER_PORT) {
	id = 0;
}

Server::~Server() {
	
}

void Server::run() {
	running = true;
	int timer = 0;
	while (running) {
		Packet packet = socket.getPacket();
		if (packet.isValid()) {
			// GET OUR CONNECTION
			Address address = packet.getAddress();
			ClientConnection* current = NULL;
			if(connections.count(address)) {
				// proceed if connection exists
				current = connections[address];
				// current.
			} else{ // connection does not exist
				current = new ClientConnection(address,id++,socket); //handshaking happens internally
				connections[address] = current;
			}
			Command* command = Command::deserialize(packet.getData());
			if(command) {
				current->processCommand(command);
				delete command;
			}
		}
		if(timer++ % 100 == 0){
			
			std::vector<Elf> elves;
			elves.push_back((Elf) {1, 0, 0, 0, 0});
			elves.push_back((Elf) {2, 0, 1, 0, 0});
			elves.push_back((Elf) {3, 1, 0, 0, 0});
			GameState state1;
			state1.elves = elves;
			state1.felhound = (Felhound) {2,2, 0, 0};

			std::map<Address, ClientConnection*>::iterator it;
			for(it = connections.begin(); it != connections.end(); it++){
				((*it).second)->sendGameState(state1);
			}
		}

		// if(timer++ % 51 == 0){
		// 	std::vector<Elf> elves;
		// 	elves.push_back((Elf) {1, 9, 9});
		// 	elves.push_back((Elf) {2, 9, 9});
		// 	elves.push_back((Elf) {3, 9, 9});
		// 	GameState state1;
		// 	state1.elves = elves;
		// 	state1.felhound = (Felhound) {2,2};

		// 	std::map<IPaddress, ClientConnection*>::iterator it;
		// 	for(it = connections.begin(); it != connections.end(); it++){
		// 		((*it).second)->sendGameState(state1);
		// 	}
		// }

		SDL_Delay(10);
	}
}