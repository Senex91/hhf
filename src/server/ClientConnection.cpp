#include "GameState.h"
#include "ClientConnection.h"
#include <string.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "NetworkConstants.h"

ClientConnection::ClientConnection(IPaddress ad,char id) : address(ad), id(id) {
	if (!(sd = SDLNet_UDP_Open(0)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (!(p = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	p->address = address;
	
	char message[3];
	message[0] = HANDSHAKE_CMD;
	message[1] = id;
	message[2] = 0;
	sendText(std::string(message));
}

ClientConnection::~ClientConnection() {
	
}

void ClientConnection::sendGameState(const GameState& gamestate){
	sendText(serializeGameState(gamestate));
	
}

void ClientConnection::sendText(const std::string& text) {
	memcpy (p->data, text.c_str(),text.size()+1);
	p->len = (text.size() + 1);
	SDLNet_UDP_Send(sd, -1, p);
}
