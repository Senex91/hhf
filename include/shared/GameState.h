#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <string>

struct Elf{
    int id;
    double x;
    double y;
	
	double xvel;
	double yvel;
};

struct Felhound{
    double x;
    double y;
	
	double xvel;
	double yvel;
};

struct GameState{
    std::vector<Elf> elves;
    Felhound felhound;
};

std::string serializeGameState(const GameState&);
std::string gameStateToString(const GameState&);
GameState deserializeGameState(const std::string&);

#endif



