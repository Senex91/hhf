#include "ServerConnection.h"
#include <stdlib.h>
#include <stdio.h>
#include "NetworkConstants.h"
#include "Game.h"
#include <iostream>
#include <string>
#include "Command.h"
#include "Debug.h"

using std::cin;
using std::string;

ServerConnection::ServerConnection(Game&) : game(game) {
	
}

ServerConnection::~ServerConnection() {
	
}

void ServerConnection::initialize() {
	if (SDLNet_Init() < 0) {
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	
	/* Open a socket */
	if (!(socket = SDLNet_UDP_Open(0))) {
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	
	/* Make space for the packet */
	if (!(packet = SDLNet_AllocPacket(512))) {
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	
	SDLNet_ResolveHost(&packet->address,"127.0.0.1",SERVER_PORT);
	bool receivedID = false;
	while(!receivedID) {
		sendText("join");
		SDL_Delay(50);
		if(receivePacket()) {
			char* data = (char*)packet->data;
			if(data[0] == HANDSHAKE_CMD) {
				myID = data[1];
				receivedID = true;
			}
		}
	}
}

void ServerConnection::destroy() {
	
}

void ServerConnection::update() {
	/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
	if (receivePacket()) {
		printf("UDP Packet incoming\n");
		printf("\tChan:    %d\n", packet->channel);
		printf("\tData:    %s\n", (char *)packet->data);
		printf("\tLen:     %d\n", packet->len);
		printf("\tMaxlen:  %d\n", packet->maxlen);
		printf("\tStatus:  %d\n", packet->status);
		printf("\tAddress: %x %x\n", packet->address.host, packet->address.port);
		
	}
}

void ServerConnection::sendText(string text) {
	DEBUG("Sending:" << text);
	memcpy(packet->data,text.c_str(),text.size()+1);
	packet->len = text.size()+1;
	if(!SDLNet_UDP_Send(socket,-1,packet)) {
		DEBUG("UDP packet failed to send");
	}
}

bool ServerConnection::receivePacket() {
	return SDLNet_UDP_Recv(socket, packet);
}

void ServerConnection::move(const Ogre::Vector3& pos) {
	MoveCommand m(myID,pos.x,pos.z);
	sendText(m.write());
}