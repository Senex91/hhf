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
	typedef std::map<int, ElfPathPlanner*>::const_iterator it_type;
	for(it_type iterator = elfPlanners.begin(); 
		iterator != elfPlanners.end(); iterator++) {
		iterator->second->tick();
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
	state.elves[e.id] = e;

	ElfPathPlanner* planner = new ElfPathPlanner(&state, state.elves.size() -1);
	elfPlanners[e.id] = planner;
	
}

void GamePhysics::playerSetGoal(int id,double x,double y) {
	elfPlanners[id]->setGoal(x, y);
}

void GamePhysics::playerThrow(int id,int id2) {
	DEBUG("attempting throw between " << id << " and " << id2);
	elfPlanners[id]->throwOrb(id2);
}

void GamePhysics::removePlayer(int id) {



	/*
	This doesn't work 100%--
	test that breaks:
	server start
	client joins
	client quits
	client rejoins (client now doesn't have a real ogre model)
	client quits (server segfault)
	*/
	state.elves.erase(id);
	elfPlanners.erase(id);
	// state.elves.erase(state.elves.begin() + state.getIndex(id));
	// elfPlanners.erase(elfPlanners.begin() + state.getIndex(id));


	// for(vector<Elf>::iterator it = state.elves.begin(); 
	// 	it != state.elves.end(); it++) {
	// 	if((*it).id == id) {
	// 		state.elves.erase(it);
	// 		break;
	// 	}
	// }

	// for(vector<ElfPathPlanner*>::iterator it = elfPlanners.begin(); 
	// 	it != elfPlanners.end(); it++) {
	// 	if((*it)->getId() == id) {
	// 		elfPlanners.erase(it);
	// 		break;
	// 	}
	// }


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