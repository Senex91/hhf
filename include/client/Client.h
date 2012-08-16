#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "InputListener.h"

// Library constructs
#include "OgreManager.h"
#include "OISManager.h"
#include "CEGUIManager.h"

// Game entities
#include "GameRenderer.h"
#include "NetServer.h"
#include "ElfCommander.h"


/**
 * @brief Client runs a Client instance of a game.
 * The Client is a singleton that enables all subcomponents 
 * to access each other.
 */
class Client : public OIS::KeyListener, public OIS::MouseListener {
public:
	static Client& getInstance();

	inline OgreManager& getOgreManager() { return ogre; }
	inline OISManager& getOISManager() { return ois; }
	inline CEGUIManager& getCEGUIManager() { return cegui; }
	inline NetServer& getNetServer() { return server; }

	inline void setRunning(const bool& r) { running = r; }

	void initialize();
	void destroy();
	
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


	// Library constructs
	OgreManager ogre;
	OISManager ois;
	CEGUIManager cegui;

	// Game entities
	GameRenderer gameRenderer;
	NetServer server;
	ElfCommander commander;
	

	// Client state
	bool running;

};

#endif
