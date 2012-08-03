#include "NetServer.h"
#include "Debug.h"

// #include "GameState.h"


NetServer::NetServer() : socket(), serverAddress("localhost",SERVER_PORT), latestState() {
	handshaked = false;
	id = -1;
	std::vector<Elf> elves;
    elves.push_back((Elf) {0, 0, 0, 0, 0});
    elves.push_back((Elf) {1, 4, 4, 0, 0});
    latestState.elves = elves;
    latestState.felhound = (Felhound) {2, 2, 0, 0};
	
}

NetServer::~NetServer(){

}

void NetServer::receiveData() {
	Packet p = socket.getPacket();
	while(p.isValid()) { //exhaust the packet buffer
		// DEBUG("Received packet:" << p.getData());
		Command* c = Command::deserialize(p.getData());
		if(c == NULL) {
			DEBUG("Received invalid packet:" << p.getData());
		} else {
			c->visit(*this);
			delete c;
		}
		p = socket.getPacket(); //pull up the next one
	}
	if(!handshaked) {
		Packet send(JoinCommand().write());
		send.setAddress(serverAddress);
		socket.sendPacket(send);
	}
}

GameState const& NetServer::getGameState(){
	// latestState.elves[0].y = latestState.elves[0].y + 0.01;
	// latestState.elves[0].x = latestState.elves[0].x + 0.01;

	// latestState.felhound.x = latestState.felhound.x + 1;
	// latestState.felhound.y = latestState.felhound.y + 1;

	return latestState;
}

void NetServer::accept(JoinCommand&) {
	DEBUG("NetServer::accept: Did not expect a JoinCommand from the server.");
}

void NetServer::accept(IDCommand& idCmd) {
	handshaked = true;
	id = idCmd.getID();
}

void NetServer::accept(GameStateCommand& gsc) {
	latestState = gsc.getGameState();
}

void NetServer::accept(MoveCommand&) {
	DEBUG("NetServer::accept: Did not expect a MoveCommand from the server.");
}

void NetServer::accept(BlinkCommand&) {
	DEBUG("NetServer::accept: Did not expect a BlinkCommand from the server.");
}