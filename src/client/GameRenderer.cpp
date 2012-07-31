#include "GameRenderer.h"

#include "Debug.h"


GameRenderer::GameRenderer(){

}

GameRenderer::~GameRenderer(){

}

void GameRenderer::renderNextState(GameState const& newState){
	DEBUG(gameStateToString(newState));

}

