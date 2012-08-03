#ifndef OIS_MANAGER_H
#define OIS_MANAGER_H

#include <OgreWindowEventUtilities.h>
#include <OIS.h>

// listeners
#include "InputListener.h"
#include <set>

class OISManager : 
	public OIS::KeyListener, 
	public OIS::MouseListener,
	public Ogre::WindowEventListener {
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

	OIS::Mouse* getMouse() { return mouse; }
	OIS::Keyboard* getKeyboard() { return keyboard; }


	// Input Listeners
	void addMouseListener(OIS::MouseListener*);
	void addKeyListener(OIS::KeyListener*);
	void removeMouseListener(OIS::MouseListener*);
	void removeKeyListener(OIS::KeyListener*);

protected:
	// Ogre::WindowEventListener
    //Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
	
private:
	
	OIS::InputManager* inputManager;
	OIS::Mouse*    mouse;
	OIS::Keyboard* keyboard;

	// Input Listeners
	std::set<OIS::MouseListener*> mouseListeners;
	std::set<OIS::KeyListener*> keyListeners;
};


#endif