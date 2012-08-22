#include "Debug.h"
#include "NetManager.h"
#include "Command.h"
#include "Server.h"

#include <SDL.h>
#include "GameMaster.h"

using std::cout;
using std::endl;

int main() {
	//SDL_Init(SDL_INIT_EVERYTHING);
	//SDLNet_Init();
	DEBUG("Launching Server... please stand by...");

	Server& s = Server::getInstance();
	s.run();
	// GamePhysics physics;

	// GameMaster master(NULL);
	// while(true){
	// 	DEBUG("tick");


	// 	SDL_Delay(1000);
	// }
	
	return 0;
}
