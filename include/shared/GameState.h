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

	bool alive;
};


struct Felhound {
    double x;
    double y;
	
	double xvel;
	double yvel;

	double orientation;

	bool alive;
};

struct Orb {
	double x;
	double y;
	
	int id;

	bool alive;
};

struct GameState{
	std::vector<Elf> elves;
	Felhound felhound;
	Orb orb;
	
    GameState(void);
    GameState(const GameState&);
    const GameState& operator=(const GameState&);

    int getIndex(int);

};

std::string serializeGameState(const GameState&);
std::string gameStateToString(const GameState&);
GameState deserializeGameState(const std::string&);

#endif



