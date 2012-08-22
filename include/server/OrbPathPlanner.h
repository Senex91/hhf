#ifndef ORB_PATH_PLANNER_H
#define ORB_PATH_PLANNER_H

#include "GameState.h"

/**
 * @brief An OrbPathPlanner
 */
class OrbPathPlanner {
public:

	OrbPathPlanner(GameState*);
	~OrbPathPlanner();

	void tick();
	
private:

	GameState* state;

};

#endif