#include "GameState.h"
#include "NetClient.h"
#include <string.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "NetworkConstants.h"
#include "Debug.h"

NetClient::NetClient(Address ad,int id,Socket& sd) : address(ad), socket(sd) {
	this->id = id;
	sendText(IDCommand(id).write());
}

NetClient::~NetClient() {
	
}

void NetClient::sendGameState(const GameState& gamestate){
	sendText(GameStateCommand(gamestate).write());
	
}

void NetClient::sendText(const std::string& text) {
	Packet send(text);
	send.setAddress(address);
	socket.sendPacket(send);
}

void NetClient::processCommand(Command* c) {
	if(c == NULL) {
		DEBUG("NetClient::processCommand: unrecognized command");
	}
	c->visit(*this);
}

void NetClient::accept(JoinCommand&) {
	
}

void NetClient::accept(IDCommand&) {
	
}

void NetClient::accept(GameStateCommand&) {
	
}

void NetClient::accept(MoveCommand&) {
	
}

void NetClient::accept(BlinkCommand&) {
	
}