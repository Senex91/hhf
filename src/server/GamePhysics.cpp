#include "GamePhysics.h"
#include "GameState.h"
#include <cmath>

using std::vector;
using std::pow;
using std::sqrt;

GamePhysics::GamePhysics() {
	state.felhound = (Felhound){0, 0, 0, 0};
	
}

GamePhysics::~GamePhysics() {
	
}

void GamePhysics::tick() {
	double dt = 0.001; //TODO: timers
	
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
			return;
		}
	}
}