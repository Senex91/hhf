#ifndef ORB_PATH_PLANNER_H
#define ORB_PATH_PLANNER_H

#include "GameState.h"

#define ORB_VELOCITY 40.0

/**
 * @brief An OrbPathPlanner
 */
class OrbPathPlanner {
public:

	OrbPathPlanner(GameState*);
	~OrbPathPlanner();

	void tick();

	// void spawn();
	// void unSpawn();
	
private:

	GameState* state;
};

#endif