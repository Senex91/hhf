#ifndef ELF_PATH_PLANNER_H
#define ELF_PATH_PLANNER_H

#include "GameState.h"

#define VELOCITY 20.0

/**
 * @brief An ElfPathPlanner
 */
class ElfPathPlanner {
public:

	ElfPathPlanner(GameState*, int);
	~ElfPathPlanner();

	void tick();

	void setGoal(double x, double y);
	
private:

	GameState* state;
	int index;

};

#endif