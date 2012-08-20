#ifndef ROUND_H
#define ROUND_H

#include "GamePhysics.h"

/**
 * @brief A Round produces gameplay until one player dies.
 *
 * A Round contains game ritual mechanics-- 
 * player spawn, orb spawn, felhound spawn, and a death ritual
 * for the dead player.
 */
class Round {
public:
	Round();
	~Round();

	void playStep();

	bool isEnded();
	
private:

	GamePhysics* physics; //TODO how this gets here

	int initialNumPlayers;
	
};

#endif