#ifndef MAP_H
#define MAP_H

class Game;

class Map {
public:
	Map(Game& game);
	~Map();
	
	void initialize();
	void destroy();
	
	void update();
	
private:
	Game& game;
};

#endif