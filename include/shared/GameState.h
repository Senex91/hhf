#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <map>
#include <string>


struct ElfColor {
	float r;
	float g;
	float b;
};

enum ElfState {
	ELF_UNSPAWNED=0,
	ELF_SPAWNED=1,
	ELF_DEAD=2,
	ELF_SPECTATING=3
};

struct Elf {
    int id;

    // Physical state
    double x;
    double y;
	
	double xvel;
	double yvel;
	
	double orientation;
	
	double xgoal;
	double ygoal;

	//Color
	ElfColor color;

	//
	ElfState state;
};

enum FelhoundState {
	FELHOUND_UNSPAWNED=0,
	FELHOUND_SPAWNED=1,
	FELHOUND_FEEDING=2
};

struct Felhound {
    double x;
    double y;
	
	double xvel;
	double yvel;

	double orientation;

	FelhoundState state;
};

enum OrbState {
	ORB_UNSPAWNED=0,
	ORB_SPAWNED=1
};

struct Orb {
	double x;
	double y;
	
	int id;

	OrbState state;
};

struct GameState{
	std::map<int, Elf> elves;
	Felhound felhound;
	Orb orb;
	
    GameState(void);
    GameState(const GameState&);
    const GameState& operator=(const GameState&);

    // int getIndex(int);

};

std::string serializeGameState(const GameState&);
std::string gameStateToString(const GameState&);
GameState deserializeGameState(const std::string&);

#endif



