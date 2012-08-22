#ifndef POINT_H
#define POINT_H

#include "Round.h"

#include "GamePhysics.h"

/**
 * @brief A Point produces gameplay until a player wins a point.
 *
 * Players win a point by being the last man standing.
 * Players are killed by being in contact with a felhound-- which
 * occurs in a Round.
 *
 * A Point begins by spawning all players.
 * A Point ends with a death ritual where the final player
 * and felhound are removed.
 */
class Point {
public:
	Point(GamePhysics*);
	~Point();

	void playStep();

	bool isEnded();
	
private:

	Round* getCurrentRound();
	Round* current;

	void spawnPlayers();
	bool playersSpawned;


	GamePhysics* physics; // TODO how this gets here

	

};

#endif