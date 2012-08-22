#ifndef FELHOUND_PATH_PLANNER_H
#define FELHOUND_PATH_PLANNER_H

#include "GameState.h"

#define ACCEL 0.02

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

	double felhoundAcceleration;

};

#endif