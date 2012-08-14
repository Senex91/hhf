#include "NetManager.h"
#include <cstdlib>
#include <cstdio>
#include "Debug.h"
#include "Server.h"

NetManager::NetManager(): socket(SERVER_PORT) {
	id = 0;
}

NetManager::~NetManager() {
	
}

void NetManager::update() {
	//Exhaust packet buffer
	Packet packet = socket.getPacket();
	while(packet.isValid()) {
		DEBUG("Received packet:" << packet.getData());
		// GET OUR CONNECTION
		Address address = packet.getAddress();
		NetClient* current = NULL;
		if(connections.count(address)) {
			DEBUG("i know this dude already");
			// proceed if connection exists
			current = connections[address];
			// current.
		} else{ // connection does not exist
			DEBUG("got a new client");
			current = new NetClient(address,id++,socket); //handshaking happens internally
			connections[address] = current;
		}
		Command* command = Command::deserialize(packet.getData());
		if(command) {
			current->processCommand(command);
			delete command;
		} else {
			DEBUG("i don't recognize this command");
		}
		//Pull the next out of the buffer
		packet = socket.getPacket();
	}
	//send state only every 25 ticks (one tick per millisecond at the moment) to avoid spamming packets
	if(timer++ % 25 == 0) {
		const GameState& state = Server::getInstance().getGamePhysics().getState();
		for(std::map<Address,NetClient*>::iterator it = connections.begin(); it != connections.end(); it++){
			(it->second)->sendGameState(state);
		}
	}
}

NetClient* NetManager::getClient(int id) {
	for(std::map<Address,NetClient*>::iterator it = connections.begin(); it != connections.end(); it++){
		if((it->second)->getID() == id) {
			return it->second;
		}
	}
	return NULL;
}

void NetManager::removeClient(int id) {
	for(std::map<Address,NetClient*>::iterator it = connections.begin(); it != connections.end(); it++){
		if((it->second)->getID() == id) {
			delete (it->second);
			connections.erase(it);
			return;
		}
	}
}