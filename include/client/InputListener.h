#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <OIS.h>

/**
 * @brief InputListener renders the game as received by the server.
 */
class InputListener {
public:
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

private:

};
#endif
