#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <string>

struct Elf{
    double x;
    double y;
    int id;
};

struct Felhound{
    double x;
    double y;
};

struct GameState{
    std::vector<Elf> elves;
    Felhound felhound;
};

std::string serializeGameState(const GameState&);
GameState deserializeGameState(const std::string&);

#endif



