#include "HeadlessClient.h"
#include "Debug.h"

#include "main.h"
#include <SDL.h>
#include <SDL_net.h>
#include <string>

int main() {
	//SDL_Init(SDL_INIT_EVERYTHING);
    //SDLNet_Init();

    DEBUG("starting client");

    HeadlessClient& client = HeadlessClient::getInstance();
    // DEBUG("RUNNING CLIENT...............................");
    client.initialize();
    client.run();

    client.destroy();

	return 0;
}