#include "Server.h"
#include <SDL.h>

Server& Server::getInstance() {
	static Server instance;
	return instance;
}

Server::Server() {
	
}

Server::~Server() {
	
}

void Server::run() {
	running = true;
	while(running) {
		phys.tick();
		net.update();
		//SDL_Delay(10);
	}
}