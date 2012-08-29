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

	// State operations
	// void spawn();	//enter with god rays
	// void unSpawn();	//vanish 
	// void die();		//suffer and vanish
	
private:

	GameState* state;
	double felhoundAcceleration;

};

#endif