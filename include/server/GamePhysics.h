#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include "GameState.h"

class GamePhysics {
public:
	GamePhysics();
	~GamePhysics();
	
	const GameState& getState() { return state; }
	
	void addPlayer(int id);
	void tick();
	
private:
	GamePhysics(const GamePhysics&) {}
	const GamePhysics& operator=(const GamePhysics& other) { return *this; }
	GameState state;
};


#endif