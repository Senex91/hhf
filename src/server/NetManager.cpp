#include "NetManager.h"
#include <cstdlib>
#include <cstdio>
#include "Debug.h"

NetManager::NetManager(): socket(SERVER_PORT) {
	id = 0;
}

NetManager::~NetManager() {
	
}

void NetManager::run() {
	running = true;
	int timer = 0;
	while (running) {
		//Exhaust packet buffer
		Packet packet = socket.getPacket();
		while(packet.isValid()) {
			// GET OUR CONNECTION
			Address address = packet.getAddress();
			NetClient* current = NULL;
			if(connections.count(address)) {
				// proceed if connection exists
				current = connections[address];
				// current.
			} else{ // connection does not exist
				current = new NetClient(address,id++,socket); //handshaking happens internally
				connections[address] = current;
			}
			Command* command = Command::deserialize(packet.getData());
			if(command) {
				current->processCommand(command);
				delete command;
			}
			//Pull the next out of the buffer
			packet = socket.getPacket();
		}
		if(timer++ % 100 == 0){
			
			std::vector<Elf> elves;
			elves.push_back((Elf) {1, 0, 0, 0, 0});
			elves.push_back((Elf) {2, 0, 1, 0, 0});
			elves.push_back((Elf) {3, 1, 0, 0, 0});
			GameState state1;
			state1.elves = elves;
			state1.felhound = (Felhound) {2,2, 0, 0};

			std::map<Address, NetClient*>::iterator it;
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

		// 	std::map<IPaddress, NetClient*>::iterator it;
		// 	for(it = connections.begin(); it != connections.end(); it++){
		// 		((*it).second)->sendGameState(state1);
		// 	}
		// }

		SDL_Delay(10);
	}
}