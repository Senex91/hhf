#include "GameState.h"
#include "ClientConnection.h"
#include "string.h"
#include "string"
#include <stdlib.h>
#include <stdio.h>

ClientConnection::ClientConnection(IPaddress ad) : address(ad) {
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
}

ClientConnection::~ClientConnection() {
	
}

void ClientConnection::sendGameState(const GameState& gamestate){
	std::string toSend = serializeGameState(gamestate);
	memcpy (p->data, toSend.c_str(),toSend.size()+1);
	//p->data = reinterpret_cast<const Uint8*>(toSend.c_str());
	p->len = (toSend.size() + 1);

	SDLNet_UDP_Send(sd, -1, p);

}
