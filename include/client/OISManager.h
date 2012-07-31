#ifndef OIS_MANAGER_H
#define OIS_MANAGER_H

#include <OIS.h>

class OISManager : public OIS::KeyListener, public OIS::MouseListener {
public:
	OISManager();
	~OISManager();
	
	void initialize();
	void destroy();
	
	void update();
	
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	
private:
	
	OIS::InputManager* inputManager;
	OIS::Mouse*    mouse;
	OIS::Keyboard* keyboard;
};


#endif