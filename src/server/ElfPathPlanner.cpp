#include "ElfPathPlanner.h"


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



ElfPathPlanner::ElfPathPlanner(GameState* gameState, int gameid){
	state = gameState;
	id = gameid;
}

ElfPathPlanner::~ElfPathPlanner(){

}

void ElfPathPlanner::tick(){
	double dt = 0.001; //TODO: timers

	// Elf* elf = NULL;
	// for (unsigned int i = 0; i<state->elves.size(); i++){
	// 	if (state->elves)
	// }

	if( state->elves.count(id) != 0){
		Elf& elf = state->elves[id];

		if(dist(elf.xgoal,elf.ygoal,elf.x,elf.y)<dt*VELOCITY) {
			elf.x = elf.xgoal;
			elf.y = elf.ygoal;
			elf.xvel = 0;
			elf.yvel = 0;
		} else { //otherwise, standard kinematics
			elf.x += elf.xvel * dt;
			elf.y += elf.yvel * dt;
		}
	}

	

}

void ElfPathPlanner::setGoal(double x, double y){

	if( state->elves.count(id) != 0){
		Elf& elf = state->elves[id];

		double ds = dist(x,y,elf.x,elf.y);
		double xdir = (x-elf.x)/ds;
		double ydir = (y-elf.y)/ds;
		//TODO: gradual turning
		elf.xvel = xdir * VELOCITY; 
		elf.yvel = ydir * VELOCITY;
		elf.xgoal = x;
		elf.ygoal = y;
		elf.orientation = atan2(elf.xvel,elf.yvel);
	}

}

void ElfPathPlanner::throwOrb(int targetId){

	// int throwerIndex = state->getIndex(id);
	// int catcherIndex = state->getIndex(targetId);

	// if (throwerIndex != -1 && 
	// 	catcherIndex != -1){
	// 	Elf& thrower = state->elves[throwerIndex];

	// 	if(thrower.id == state->orb.id &&
	// 		dist(state->orb.x,
	// 			state->orb.y,
	// 			thrower.x,
	// 			thrower.y) < 0.05) {

	// 		state->orb.id = targetId;
	// 	}
	// }
}