#ifndef GameRenderer_H
#define GameRenderer_H

#include "InputListener.h"

#include <map>
#include "OgreElf.h"
#include "OgreOrb.h"
#include "OgreFelhound.h"

#include <string>
#include "GameState.h"
#include "TOCameraMan.h"
#include <OIS.h>
#include <SdkTrays.h>
#include "CameraStyle.h"

/**
 * @brief GameRenderer renders the game as received by the server.
 */
class GameRenderer : public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener, public Ogre::FrameListener {
public:
	GameRenderer();
	~GameRenderer();
	
	void initialize();
	void destroy();
	
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	
	
	void renderNextState(GameState const& );
	
protected:
	
	// Ogre::FrameListener
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
private:
	
	OgreBites::SdkTrayManager* mTrayMgr;
	
	std::map<int, OgreElf*> elves;
	std::map<std::string,CameraStyle*> cameraStyles;
	OgreOrb* orb;
	OgreFelhound* felhound;
	
	
};
#endif
