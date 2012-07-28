#ifndef MAP_H
#define MAP_H

#include <GameState.h>

class Game;

class Map {
public:
	Map(Game& game);
	~Map();
	
	void initialize();
	void destroy();
    
    void setGameState(GameState);
	
	void update();
	
private:
	Game& game;
    GameState gameState;
};

#endif
