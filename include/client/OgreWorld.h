#ifndef OGREWORLD_H
#define OGREWORLD_H

#include "GameState.h"
/**
 * @brief An OgreWorld draws a gamestate.
 */
class OgreWorld {
public:
	OgreWorld();
	~OgreWorld();

	void drawGameState(GameState);
	
private:

};
#endif