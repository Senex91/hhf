#include <iostream>

#include <ClientConnection.h>
#include "SDL_net.h"

using std::cout;
using std::endl;

int main() {
	cout << "TODO: write server" << endl;
	IPaddress address;
	SDLNet_ResolveHost(&address, "127.0.0.1", 2000);

	ClientConnection connection(address);

	GameState state;
	bool running = true;
	while(running){
		connection.sendGameState(state);
		SDL_Delay(1000);
	}


	// ClientConnection connection()
}
