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

inline double dist(double x1,double y1,double x2,double y2) {
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

GamePhysics::GamePhysics() {
	state.felhound = (Felhound){0, 0, 0, 0};
	state.orb = (Orb){0,0,-1};
	felhoundVelocity = 15;
}

GamePhysics::~GamePhysics() {
	
}

void GamePhysics::tick() {
	double dt = 0.001; //TODO: timers
	
	bool orbOwnerValid = false;
	Elf* orbOwner = NULL;
	
	for(vector<Elf>::iterator it = state.elves.begin(); it != state.elves.end(); it++) {
		Elf& elf = *it;
		
		if(dist(elf.xgoal,elf.ygoal,elf.x,elf.y)<dt*PLAYER_VELOCITY) {
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
			orbOwner = &elf;
			//TODO: fly towards player
			//state.orb.x = elf.x;
			//state.orb.y = elf.y;
			
			double ds = dist(state.orb.x,state.orb.y,elf.x,elf.y);
			if(ds > 0) {
				double xdir = (elf.x-state.orb.x)/ds;
				double ydir = (elf.y-state.orb.y)/ds;
				
				if(ds < dt*ORB_VELOCITY) {
					state.orb.x = elf.x;
					state.orb.y = elf.y;
				} else {
					state.orb.x += xdir * dt * ORB_VELOCITY;
					state.orb.y += ydir * dt * ORB_VELOCITY;
				}
			}
		}
	}
	if(!orbOwnerValid && state.elves.size()>0) { //Need at least one elf 
		state.orb.id = state.elves[0].id;
		state.orb.x = state.elves[0].x;
		state.orb.y = state.elves[0].y;
	}

	if(orbOwnerValid){
		double ds = dist(state.orb.x,state.orb.y,state.felhound.x,state.felhound.y);
		if(ds > 0.1) {
			double ds2 = pow(ds,1.5);
			double xdir = (state.orb.x-state.felhound.x)/ds2;
			double ydir = (state.orb.y-state.felhound.y)/ds2;
			state.felhound.orientation = atan2(state.felhound.xvel,state.felhound.yvel);

			state.felhound.xvel += xdir * felhoundVelocity;
			state.felhound.yvel += ydir * felhoundVelocity;

			felhoundVelocity+= FELHOUND_ACCEL * dt;

		} else { //Felhound is at orb
			//Kill the player if the orb is at a player
			if(dist(state.orb.x,state.orb.y,orbOwner->x,orbOwner->y)<0.1) {
				removePlayer(orbOwner->id);
			}
		}
		
		state.felhound.x += state.felhound.xvel * dt;
		state.felhound.y += state.felhound.yvel * dt;
	}
	
}

void GamePhysics::addPlayer(int id) {
	srand(unsigned(time(0)));

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
	if(thrower && thrower->id == state.orb.id && catcher) {
		if(dist(state.orb.x,state.orb.y,thrower->x,thrower->y) < 0.05) { //Orb has to be near you
			state.orb.id = id2;
		}
	}
}

void GamePhysics::removePlayer(int id) {
	for(vector<Elf>::iterator it = state.elves.begin(); it != state.elves.end(); it++) {
		if((*it).id == id) {
			state.elves.erase(it);
			return;
		}
	}
}