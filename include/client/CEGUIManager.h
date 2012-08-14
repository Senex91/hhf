#ifndef CEGUI_MANAGER_H
#define CEGUI_MANAGER_H

#include "OISManager.h"
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

class CEGUIManager : public OIS::KeyListener, public OIS::MouseListener {
public:
	CEGUIManager();
	~CEGUIManager();
	
	void initialize();
	void destroy();
	
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	
	
private:
	CEGUI::OgreRenderer* renderer;
};


#endif