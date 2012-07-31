#include "OgreWorld.h"

#include "Debug.h"


OgreWorld::OgreWorld(){

}

OgreWorld::~OgreWorld(){

}

void OgreWorld::drawGameState(GameState const& state){

	DEBUG(gameStateToString(state));

}

