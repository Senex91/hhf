#include "ClientConnection.h"
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