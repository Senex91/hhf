#include "OrbPathPlanner.h"

#include <cmath>
#include "Debug.h"
#include <stdlib.h>

using std::vector;
using std::pow;
using std::sqrt;
using std::atan2;
using std::sin;
using std::cos;
using std::min;
using std::max;
using std::abs;

inline double dist(double x1,double y1,double x2,double y2) {
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

OrbPathPlanner::OrbPathPlanner(GameState* gameState){
	state = gameState;
}

OrbPathPlanner::~OrbPathPlanner(){

}

void OrbPathPlanner::tick(){


	double dt = 0.001; //TODO: timers

	
	if(state->orb.id != -1){

		Elf&  elf = state->elves[state->getIndex(state->orb.id)];

		double ds = dist(state->orb.x,state->orb.y,elf.x,elf.y);
		if(ds > 0) {
			double xdir = (elf.x-state->orb.x)/ds;
			double ydir = (elf.y-state->orb.y)/ds;
			
			//if we're close enough, we are on the elf
			if(ds < dt * ORB_VELOCITY) {
				state->orb.x = elf.x;
				state->orb.y = elf.y;
			} else {
				//otherwise, standard kinematics
				state->orb.x += xdir * dt * ORB_VELOCITY;
				state->orb.y += ydir * dt * ORB_VELOCITY;
			}
		}

	}else{
		//hacky orb spawn
		if (state->elves.size() > 0){
			state->orb.id = state->elves[0].id;
			state->orb.x = state->elves[0].x;
			state->orb.y = state->elves[0].y;
		}

	}


}