#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <string>


struct ElfColor {
	float r;
	float g;
	float b;
};

struct Elf {
    int id;		//must start at 0
    double x;
    double y;
	
	double xvel;
	double yvel;
	
	double orientation;
	
	double xgoal;
	double ygoal;

	ElfColor color;
};


struct Felhound {
    double x;
    double y;
	
	double xvel;
	double yvel;
};

struct Orb {
	double x;
	double y;
	
	int id;
};

struct GameState{
	std::vector<Elf> elves;
	Felhound felhound;
	Orb orb;
	
    GameState(void);
    GameState(const GameState&);
    const GameState& operator=(const GameState&);
};

std::string serializeGameState(const GameState&);
std::string gameStateToString(const GameState&);
GameState deserializeGameState(const std::string&);

#endif



