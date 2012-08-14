
#include "Client.h"
#include "Debug.h"

#include <SDL.h>
#include <SDL_net.h>
#include <string>

int main(){
	//SDL_Init(SDL_INIT_EVERYTHING);
	//SDLNet_Init();
	
	DEBUG("starting client");

	Client& client = Client::getInstance();
	// DEBUG("RUNNING CLIENT...............................");
	client.initialize();
	client.run();

	client.destroy();

	return 0;
}



