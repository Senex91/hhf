#ifndef GameRenderer_H
#define GameRenderer_H

#include "InputListener.h"

#include <map>
#include "Elf.h"

#include <string>
#include "GameState.h"
#include "TOCameraMan.h"

/**
 * @brief GameRenderer renders the game as received by the server.
 */
class GameRenderer : public InputListener {
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
