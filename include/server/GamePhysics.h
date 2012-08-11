#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#define PLAYER_VELOCITY 20.0
#define ORB_VELOCITY 40.0

#include "GameState.h"

class GamePhysics {
public:
	GamePhysics();
	~GamePhysics();
	
	const GameState& getState() { return state; }
	
	void addPlayer(int id);
	void tick();
	
	void playerSetGoal(int id,double x,double y);
	void playerThrow(int id,int id2);
	
private:
	GamePhysics(const GamePhysics&) {}
	const GamePhysics& operator=(const GamePhysics& other) { return *this; }
	GameState state;
};


#endif