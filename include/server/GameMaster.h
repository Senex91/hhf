#ifndef GAME_MASTER_H
#define GAME_MASTER_H

#include "Point.h"
#include "GamePhysics.h"
#include "Game.h"

/**
 * @brief A GameMaster conducts games, and allows players to join the game.
 */
class GameMaster {
public:

	GameMaster(GamePhysics*);
	~GameMaster();

	void playStep();

private:

	Game* getCurrentGame();
	Game* current;

	GamePhysics* physics;
	
};

#endif