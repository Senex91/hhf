#ifndef MAP_H
#define MAP_H

#include <GameState.h>

// #include "map"
#include "Elf.h"

// class Game;

class Map {
public:
	Map();
	~Map();
	
	void initialize();
	void destroy();
    
    void setGameState(const GameState&);
	
	void update();
	
private:
	// Game& game;
    GameState gameState;

    // std::map<int, OgreElf*> elves;
};

#endif
