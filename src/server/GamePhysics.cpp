#include "GamePhysics.h"
#include "GameState.h"
#include <cmath>
#include "Debug.h"

using std::vector;
using std::pow;
using std::sqrt;
using std::atan2;

GamePhysics::GamePhysics() {
	state.felhound = (Felhound){0, 0, 0, 0};
	state.orb = (Orb){0,0,-1};
}

GamePhysics::~GamePhysics() {
	
}

void GamePhysics::tick() {
	double dt = 0.001; //TODO: timers
	
	bool orbOwnerValid = false;
	
	for(vector<Elf>::iterator it = state.elves.begin(); it != state.elves.end(); it++) {
		Elf& elf = *it;
		
		if(sqrt(pow(elf.xgoal-elf.x,2)+pow(elf.ygoal-elf.y,2))<dt*PLAYER_VELOCITY) {
			elf.x = elf.xgoal;
			elf.y = elf.ygoal;
			elf.xvel = 0;
			elf.yvel = 0;
		} else {
			elf.x += elf.xvel * dt;
			elf.y += elf.yvel * dt;
		}
		if(state.orb.id == elf.id) {
			orbOwnerValid = true;
			//TODO: fly towards player
			state.orb.x = elf.x;
			state.orb.y = elf.y;
		}
	}
	if(!orbOwnerValid && state.elves.size()>0) { //Need at least one elf 
		state.orb.id = state.elves[0].id;
	}
}

void GamePhysics::addPlayer(int id) {
	Elf e = { id, 0, 0, 0, 0, 0, 0};
	state.elves.push_back(e);
	
}

void GamePhysics::playerSetGoal(int id,double x,double y) {
	for(vector<Elf>::iterator it = state.elves.begin(); it != state.elves.end(); it++) {
		Elf& elf = *it;
		if(elf.id == id) {
			double xdir = (x-elf.x)/sqrt(pow(x-elf.x,2)+pow(y-elf.y,2));
			double ydir = (y-elf.y)/sqrt(pow(x-elf.x,2)+pow(y-elf.y,2));
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
	if(thrower && thrower->id == state.orb.id && catcher) {
		state.orb.id = id2;
	}
}