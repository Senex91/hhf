#ifndef FELHOUND_PATH_PLANNER_H
#define FELHOUND_PATH_PLANNER_H

#include "GameState.h"

/**
 * @brief An FelhoundPathPlanner
 */
class FelhoundPathPlanner {
public:

	FelhoundPathPlanner(GameState*);
	~FelhoundPathPlanner();

	void tick();
	
private:

	GameState* state;

};

#endif