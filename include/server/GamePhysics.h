#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#define PLAYER_VELOCITY 20.0
// #define ORB_VELOCITY 40.0
#define START_RADIUS 25.0
#define FELHOUND_ACCEL 0.02

#include "GameState.h"
#include "ElfPathPlanner.h"
#include "FelhoundPathPlanner.h"
#include "OrbPathPlanner.h"

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

	GameState getGameState();

	// Element state control
	void unQueuePlayers();
	void unSpawnPlayers(std::vector<int>);
	void spawnPlayers();
	void spawnOrb();
	void spawnFelhound();
	void agroFelhound();


	int getNumAlivePlayers();
	std::vector<int> getAlivePlayers();
	int getMaxPlayerPoints();

	bool isOrbSpawned();
	bool isFelhoundSpawned();
	bool isFelhoundResting();
	bool arePlayersSpawned();

	
private:
	GamePhysics(const GamePhysics&) {}
	const GamePhysics& operator=(const GamePhysics& other) { return *this; }
	GameState state;

	double felhoundAcceleration;

	std::map<int, ElfPathPlanner*> elfPlanners;
	FelhoundPathPlanner* felhoundPlanner;
	OrbPathPlanner* orbPlanner;


};


#endif