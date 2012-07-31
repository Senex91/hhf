#include "GameRenderer.h"

#include "Debug.h"


GameRenderer::GameRenderer(): server(), world(){

}

GameRenderer::~GameRenderer(){

}

void GameRenderer::renderNextState(){
	GameState state = server.getGameState();
	world.drawGameState(state);
	// DEBUG(gameStateToString(newState));

}

