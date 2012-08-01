#include "GameState.h"
#include "ClientConnection.h"
#include <string.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "NetworkConstants.h"
#include "Debug.h"

ClientConnection::ClientConnection(Address ad,int id,Socket& sd) : address(ad), socket(sd) {
	this->id = id;
	sendText(IDCommand(id).write());
}

ClientConnection::~ClientConnection() {
	
}

void ClientConnection::sendGameState(const GameState& gamestate){
	sendText(GameStateCommand(gamestate).write());
	
}

void ClientConnection::sendText(const std::string& text) {
	Packet send(text);
	send.setAddress(address);
	socket.sendPacket(send);
}

void ClientConnection::processCommand(Command* c) {
	if(c == NULL) {
		DEBUG("ClientConnection::processCommand: unrecognized command");
	}
	c->visit(*this);
}

void ClientConnection::accept(JoinCommand&) {
	
}

void ClientConnection::accept(IDCommand&) {
	
}

void ClientConnection::accept(GameStateCommand&) {
	
}

void ClientConnection::accept(MoveCommand&) {
	
}

void ClientConnection::accept(BlinkCommand&) {
	
}