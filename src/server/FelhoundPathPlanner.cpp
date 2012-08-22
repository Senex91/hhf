#include "FelhoundPathPlanner.h"

#include <cmath>
#include "Debug.h"

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

inline double clamp(double x,double minVal,double maxVal) {
	return max(minVal,min(maxVal,x));
}

FelhoundPathPlanner::FelhoundPathPlanner(GameState* gameState){
	state = gameState;
	felhoundAcceleration = 0;

}

FelhoundPathPlanner::~FelhoundPathPlanner(){

}

void FelhoundPathPlanner::tick(){

	double dt = 0.001; //TODO: timers

	/***
	FELHOUND PATH PLANNING
	****/
	double ds = dist(state->orb.x,state->orb.y,state->felhound.x,state->felhound.y);
	if(ds > 0.1) { //far away from orb

		double xdir = state->orb.x-state->felhound.x;
		double ydir = state->orb.y-state->felhound.y;
		state->felhound.orientation = 
			atan2(state->orb.y-state->felhound.y,
				state->orb.x-state->felhound.x);
		
		if(xdir > 0) {
			state->felhound.xvel += felhoundAcceleration;
		} else {
			state->felhound.xvel -= felhoundAcceleration;
		}
		if(ydir > 0) {
			state->felhound.yvel += felhoundAcceleration;
		} else {
			state->felhound.yvel -= felhoundAcceleration;
		}

		felhoundAcceleration += dt / 400.0; //TODO magic number

	} else { //Felhound is at orb

		

		//Kill the player if the orb is at a player
		// if(dist(state->orb.x,state->orb.y,orbOwner->x,orbOwner->y)<0.1) {
		// 	felhoundAcceleration = 0;
		// 	// removePlayer(orbOwner->id);
		// }
	}
	
	//normal kinematics
	state->felhound.xvel = clamp(state->felhound.xvel,-40,40);
	state->felhound.yvel = clamp(state->felhound.yvel,-40,40);
	
	state->felhound.x += (dt ) * state->felhound.xvel;
	state->felhound.y += (dt ) * state->felhound.yvel;

}