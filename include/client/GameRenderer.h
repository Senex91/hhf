#ifndef GameRenderer_H
#define GameRenderer_H

#include "InputListener.h"

#include <map>
#include "OgreElf.h"

#include <string>
#include "GameState.h"
#include "TOCameraMan.h"

#include <SdkTrays.h>

/**
 * @brief GameRenderer renders the game as received by the server.
 */
class GameRenderer : public InputListener, OgreBites::SdkTrayListener {
public:
	GameRenderer();
	~GameRenderer();

	void initialize();

	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );


	void renderNextState(GameState const& );
	
private:

	OgreBites::SdkCameraMan* cameraMan; // basic camera controller

    std::map<int, OgreElf*> elves;

};
#endif
