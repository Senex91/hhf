#ifndef GAME_MASTER_H
#define GAME_MASTER_H

#include "Point.h"
#include "GamePhysics.h"

/**
 * @brief A GameMaster plays a game
 * A game is played until a player reaches a limit
 * number of points to win.
 */
class GameMaster {
public:

	GameMaster(GamePhysics*);
	~GameMaster();

	void playStep();

	bool isEnded();
	
private:

	Point* getCurrentPoint();
	Point* current;

	GamePhysics* physics;
	
};

#endif