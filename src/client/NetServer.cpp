#include "NetServer.h"
#include "Debug.h"

// #include "GameState.h"


NetServer::NetServer() : socket(), serverAddress(0,0), latestState() {
	handshaked = false;
	id = -1;
}

NetServer::~NetServer(){
	
}

void NetServer::joinServer(const Address& newAddress) {
	serverAddress = newAddress;
	handshaked = false;
	id = -1;
	sendCommand(JoinCommand());
}

void NetServer::quitServer() {
	sendCommand(QuitCommand());
}

void NetServer::sendCommand(const Command& toSend){
	Packet send(toSend.write());
	send.setAddress(serverAddress);
	socket.sendPacket(send);
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
	if(!handshaked) { //TODO: make this not spam packets in an accidental DOS attack
		sendCommand(JoinCommand());
	}
}

GameState const& NetServer::getGameState() {
	
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

void NetServer::accept(ThrowCommand&) {
	DEBUG("NetServer::accept: Did not expect a ThrowCommand from the server.");
}

void NetServer::accept(SpectateCommand&) {
	DEBUG("NetServer::accept: Did not expect a SpectateCommand from the server.");
}

void NetServer::accept(QuitCommand&) {
	DEBUG("NetServer::accept: Did not expect a QuitCommand from the server.");
}

void NetServer::accept(PlayCommand&) {
	DEBUG("NetServer::acccept: Did not expect a JoinCommand from the server.");
}