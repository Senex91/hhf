#ifndef GAME_H
#define GAME_H

#include "OgreManager.h"
#include "Map.h"
#include "OISManager.h"
#include "ServerConnection.h"

class Game {
public:
	Game();
	~Game();
	
	void run();
	
	inline OgreManager& getOgreManager() { return ogre; }
	inline OISManager& getOISManager() { return ois; }
	inline Map& getMap() { return map; }
	inline const bool& getRunning() { return running; }
	
	inline void setRunning(const bool& r) { running = r; }
	
private:
	ServerConnection connection;
	OgreManager ogre;
	OISManager ois;
	Map map;
	bool running;
};

#endif