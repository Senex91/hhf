#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#define PLAYER_VELOCITY 20.0
#define ORB_VELOCITY 40.0
#define START_RADIUS 25.0
#define FELHOUND_ACCEL 0.02

#include "GameState.h"
#include "ElfPathPlanner.h"

#include <vector>

class GamePhysics {
public:
	GamePhysics();
	~GamePhysics();
	
	const GameState& getState() { return state; }
	
	void addPlayer(int id);
	void tick();
	
	void playerSetGoal(int id,double x,double y);
	void playerThrow(int id,int id2);
	void removePlayer(int id);

	// accessors for game master
	// TODO consider placing these somewhere else
	int numAlivePlayers();
	GameState getGameState();
	bool isOrbAlive();
	bool isFelhoundAlive();

	// spawners
	void spawnOrb();
	void spawnFelhound();

	
private:
	GamePhysics(const GamePhysics&) {}
	const GamePhysics& operator=(const GamePhysics& other) { return *this; }
	GameState state;

	double felhoundAcceleration;

	std::vector<ElfPathPlanner*> elfPlanners;


};


#endif