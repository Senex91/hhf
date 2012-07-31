#ifndef GameRenderer_H
#define GameRenderer_H

#include <string>

#include "NetServer.h"
#include "OgreWorld.h"
#include "GameState.h"

/**
 * @brief GameRenderer renders the game as received by the server.
 */
class GameRenderer {
public:
	GameRenderer();
	~GameRenderer();

	void renderNextState();
	
private:
	NetServer server;
	OgreWorld world;

};
#endif
