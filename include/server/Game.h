#ifndef GAME_MASTER_H
#define GAME_MASTER_H

#include "Point.h"
#include "GamePhysics.h"

/**
 * @brief A Game plays a game
 * A game is played until a player reaches a limit
 * number of points to win.
 */
class Game {
public:

	Game(GamePhysics*);
	~Game();

	void playStep();

private:

	Point* getCurrentPoint();
	Point* current;

	GamePhysics* physics;
	
};

#endif