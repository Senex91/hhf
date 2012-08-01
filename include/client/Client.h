#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "InputListener.h"

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
class Client : public InputListener {
public:
	static Client& getInstance();

	inline OgreManager& getOgreManager() { return ogre; }
	// inline OISManager& getOISManager() { return ois; }
	// inline OgreBites::SdkCameraMan& getCameraMan() { return *cameraMan; }

	inline void setRunning(const bool& r) { running = r; }

	void initialize();
	void run();

// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

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
	// OgreBites::SdkCameraMan* cameraMan;

	// Game entities
	GameRenderer gameRenderer;
	NetServer server;

	// Client state
	bool running;

};

#endif
