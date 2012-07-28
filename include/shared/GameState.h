#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>

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

#endif



