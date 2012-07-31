#ifndef CLIENT_H
#define CLIENT_H

#include <string>

// Library constructs
#include "OgreManager.h"
#include "OISManager.h"
#include "TOCameraMan.h"

// Game entities
#include "GameRenderer.h"
#include "NetServer.h"

/**
 * @brief Client runs a Client instance of a game.
 * The Client is a singleton that enables all subcomponents 
 * to access each other.
 */
class Client {
public:
	static Client& getInstance();

	inline OgreManager& getOgreManager() { return ogre; }
	inline OISManager& getOISManager() { return ois; }
	inline OgreBites::SdkCameraMan& getCameraMan() { return *cameraMan; }

	inline void setRunning(const bool& r) { running = r; }

	void run();

private:

	// Singleton things
	Client();
	Client(Client const&);
	~Client();
	Client& operator=(Client const&);
	// static Client* instance;

	// Library constructs
	OgreManager ogre;
	OISManager ois; 
	OgreBites::SdkCameraMan* cameraMan;

	// Game entities
	GameRenderer gameRenderer;
	NetServer server;

	// Client state
	bool running;

};

#endif
