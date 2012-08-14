#include "GameState.h"
#include "NetClient.h"
#include <string.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "NetworkConstants.h"
#include "Debug.h"
#include "Server.h"

NetClient::NetClient(Address ad,int id,Socket& sd) : address(ad), socket(sd) {
	this->id = id;
}

NetClient::~NetClient() {
	
}

void NetClient::sendGameState(const GameState& gamestate){
	sendText(GameStateCommand(gamestate).write());
	
}

void NetClient::sendText(const std::string& text) {
	//DEBUG("Sending packet:"<<text);
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
	sendText(IDCommand(id).write());
	Server::getInstance().getGamePhysics().addPlayer(id);
}

void NetClient::accept(IDCommand&) {
	
}

void NetClient::accept(GameStateCommand&) {
	
}

void NetClient::accept(MoveCommand& move) {
	Server::getInstance().getGamePhysics().playerSetGoal(id,move.getMoveX(),move.getMoveY());
}

void NetClient::accept(BlinkCommand&) {
	
}

void NetClient::accept(ThrowCommand& t) {
	Server::getInstance().getGamePhysics().playerThrow(id,t.getID());
}

void NetClient::accept(SpectateCommand&) {
	sendText(IDCommand(id).write());
}

void NetClient::accept(QuitCommand&) {
	DEBUG("Received quit command");
	Server::getInstance().getGamePhysics().removePlayer(id);
	Server::getInstance().getNetManager().removeClient(id);
}