#include "GamePhysics.h"
#include "GameState.h"
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
	//TODO nicer color allocation-- a huge table?
	e.color = c;
	// double ang = 2.0 * 3.1415926 * (double)rand()/(double)RAND_MAX;
	// e.x = START_RADIUS * sin(ang);
	// e.y = START_RADIUS * cos(ang);
	//TODO this stuff goes in spawning code
	e.state = ELF_SPECTATING;
	state.elves[id] = e;

	ElfPathPlanner* planner = new ElfPathPlanner(&state, id);
	elfPlanners[id] = planner;
	
}

void GamePhysics::playerSetGoal(int id,double x,double y) {
	elfPlanners[id]->setGoal(x, y);
}

void GamePhysics::playerThrow(int id,int id2) {
	// DEBUG("attempting throw between " << id << " and " << id2);
	elfPlanners[id]->throwOrb(id2);
}

void GamePhysics::removePlayer(int id) {
	state.elves.erase(id);
	elfPlanners.erase(id);
}

GameState GamePhysics::getGameState(){
	return state;
}

void GamePhysics::unQueuePlayers(){
	//moves players from queue into unspawned

}

void GamePhysics::unSpawnPlayers(std::vector<int> playerIds){
	
}

void GamePhysics::spawnPlayers(){
	//moves players from unspawned/dead to spawned

}

void GamePhysics::spawnOrb(){
	//moves orb from unspawned to spawned

}

void GamePhysics::spawnFelhound(){

}

void GamePhysics::agroFelhound(){

}

int GamePhysics::getNumAlivePlayers(){

	return -1;
}

std::vector<int> GamePhysics::getAlivePlayers(){
	return std::vector<int>();
}

int GamePhysics::getMaxPlayerPoints(){


// bool Game::isEnded(){

// 	int maxPoints = -1;

// 	std::map<int, Elf> elves = physics->getGameState().elves;

// 	typedef std::map<int, Elf>::const_iterator it_type;
// 	for(it_type iterator = elves.begin(); iterator != elves.end(); iterator++) {
// 		// Elf e = elves[i];
// 		if (iterator->second.state == ELF_SPAWNED ||
// 			iterator->second.state == ELF_UNSPAWNED ||
// 			iterator->second.state == ELF_DEAD){

// 			// TODO add elf score field
// 			if (iterator->second.x > maxPoints){
// 				maxPoints = iterator->second.x;
// 			}
// 		}
// 	}

// 	if (maxPoints < 0){
// 		//error...
// 	}

// 	return maxPoints >= 20; // TODO LIMIT constant
// }

	return -1;
}

bool GamePhysics::isOrbSpawned(){
	return false;
}

bool GamePhysics::isFelhoundSpawned(){
	return false;
}

bool GamePhysics::isFelhoundResting(){
	return false;
}

bool GamePhysics::arePlayersSpawned(){
	return false;
}