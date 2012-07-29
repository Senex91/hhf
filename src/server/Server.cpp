#include "Server.h"
#include <cstdlib>
#include <cstdio>

bool operator<(const IPaddress& l, const IPaddress& r) {
	if(l.host == r.host) {
		return r.port < r.port;
	}
	return l.host < r.host;
}

Server::Server(): connections() {
	if (SDLNet_Init() < 0) {
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (!(sd = SDLNet_UDP_Open(SERVER_PORT))) {
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	
	/* Make space for the packet */
	if (!(p = SDLNet_AllocPacket(512))) {
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}

Server::~Server() {
	
}

void Server::run() {
	running = true;
	int timer = 0;
	while (running) {
		/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
		if (SDLNet_UDP_Recv(sd, p)) {
			printf("UDP Packet incoming\n");
			printf("\tChan:    %d\n", p->channel);
			printf("\tData:    %s\n", (char *)p->data);
			printf("\tLen:     %d\n", p->len);
			printf("\tMaxlen:  %d\n", p->maxlen);
			printf("\tStatus:  %d\n", p->status);
			printf("\tAddress: %x %x\n", p->address.host, p->address.port);
			
			/* Quit if packet contains "quit" */
			if (strcmp((char *)p->data, "quit") == 0) {
				running = false;

			}

			// GET OUR CONNECTION
			ClientConnection* current = NULL;
			if(connections.count(p->address)) {
				// proceed if connection exists
				current = connections[p->address];
				// current.
			} else{ // connection does not exist
				current = new ClientConnection(p->address);
				connections[p->address] = current;
			}




		}
		if(timer++ % 100 == 0){
			std::vector<Elf> elves;
			elves.push_back((Elf) {1, 0, 0});
			elves.push_back((Elf) {2, 0, 1});
			elves.push_back((Elf) {3, 1, 0});
			GameState state1;
			state1.elves = elves;
			state1.felhound = (Felhound) {2,2};

			std::map<IPaddress, ClientConnection*>::iterator it;
			for(it = connections.begin(); it != connections.end(); it++){
				((*it).second)->sendGameState(state1);
			}
		}

		if(timer++ % 51 == 0){
			std::vector<Elf> elves;
			elves.push_back((Elf) {1, 9, 9});
			elves.push_back((Elf) {2, 9, 9});
			elves.push_back((Elf) {3, 9, 9});
			GameState state1;
			state1.elves = elves;
			state1.felhound = (Felhound) {2,2};

			std::map<IPaddress, ClientConnection*>::iterator it;
			for(it = connections.begin(); it != connections.end(); it++){
				((*it).second)->sendGameState(state1);
			}
		}


		SDL_Delay(10);





	}
}