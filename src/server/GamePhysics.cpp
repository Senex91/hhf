#include "GamePhysics.h"
#include "GameState.h"bv
#include <cmath>
#include "Debug.h"
#include <stdlib.h>
#include <time.h>

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

GamePhysics::GamePhysics() {
	state.felhound = (Felhound){0, 0, 0, 0, 0};
	state.orb = (Orb){0,0,-1};
	felhoundAcceleration = 0;
	felhoundPlanner = new FelhoundPathPlanner(&state);
	orbPlanner = new OrbPathPlanner(&state);
}

GamePhysics::~GamePhysics() {
	
}

void GamePhysics::tick() {
	for(vector<ElfPathPlanner*>::iterator it = elfPlanners.begin();
		it != elfPlanners.end(); it++ ){
		ElfPathPlanner* planner = *it;
		planner->tick();
	}
	orbPlanner->tick();
	felhoundPlanner->tick();
	
}

void GamePhysics::addPlayer(int id) {

	ElfColor c = {
		(float)rand()/(float)RAND_MAX, 
		(float)rand()/(float)RAND_MAX,
		(float)rand()/(float)RAND_MAX };
	Elf e = { id, 0, 0, 0, 0, 0, 0};
	e.color = c;
	double ang = 2.0 * 3.1415926 * (double)rand()/(double)RAND_MAX;
	e.x = START_RADIUS * sin(ang);
	e.y = START_RADIUS * cos(ang);
	state.elves.push_back(e);

	ElfPathPlanner* planner = new ElfPathPlanner(&state, state.elves.size() -1);
	elfPlanners.push_back(planner);
	
}

void GamePhysics::playerSetGoal(int id,double x,double y) {
	for(vector<Elf>::iterator it = state.elves.begin(); it != state.elves.end(); it++) {
		Elf& elf = *it;
		if(elf.id == id) {
			double ds = dist(x,y,elf.x,elf.y);
			double xdir = (x-elf.x)/ds;
			double ydir = (y-elf.y)/ds;
			//TODO: gradual turning
			elf.xvel = xdir * PLAYER_VELOCITY;
			elf.yvel = ydir * PLAYER_VELOCITY;
			elf.xgoal = x;
			elf.ygoal = y;
			elf.orientation = atan2(elf.xvel,elf.yvel);
			return;
		}
	}
}

void GamePhysics::playerThrow(int id,int id2) {
	DEBUG("attempting throw between " << id << " and " << id2);
	//Iterate through all our elves to make sure id is the current holder, and id2 exists.
	Elf* thrower = NULL;
	Elf* catcher = NULL;
	for(vector<Elf>::iterator it = state.elves.begin(); it != state.elves.end(); it++) {
		Elf& elf = *it;
		if(elf.id == id) {
			thrower = &elf;
		}
		if(elf.id == id2) {
			catcher = &elf;
		}
	}
	DEBUG("thrower: " << thrower);
	DEBUG("catcher: " << catcher);
	//only throw if sufficiently close to throwerstate
	if(thrower && thrower->id == state.orb.id && catcher) {
		if(dist(state.orb.x,state.orb.y,thrower->x,thrower->y) < 0.05) { //Orb has to be near you
			state.orb.id = id2;
			DEBUG("Throw successfull: \t orb id=" << state.orb.id);
		}
	}
	// DEBUG()
}

void GamePhysics::removePlayer(int id) {
	for(vector<Elf>::iterator it = state.elves.begin(); it != state.elves.end(); it++) {
		if((*it).id == id) {
			state.elves.erase(it);
			return;
		}
	}
}

int GamePhysics::numAlivePlayers(){
	return 1; //TODO implement
}

bool GamePhysics::isOrbAlive(){
	return true;//TODO implement
}

bool GamePhysics::isFelhoundAlive(){
	return true;//TODO implement
}

void GamePhysics::spawnOrb(){
	
}


void GamePhysics::spawnFelhound(){

}

GameState GamePhysics::getGameState(){
	return state;
}