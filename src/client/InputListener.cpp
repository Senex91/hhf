#include "InputListener.h"

// OIS::KeyListener
bool InputListener::keyPressed( const OIS::KeyEvent &arg ) {
	// InputListener::getInstance().getCameraMan().injectKeyDown(arg);
	return true;
}
bool InputListener::keyReleased( const OIS::KeyEvent &arg ) {
	// if(arg.key == OIS::KC_F12) {
	// 	InputListener::getInstance().setRunning(false);
	// }
	// InputListener::getInstance().getCameraMan().injectKeyUp(arg);
	return true;
}
// OIS::MouseListener
bool InputListener::mouseMoved( const OIS::MouseEvent &arg ) {
	// InputListener::getInstance().getCameraMan().injectMouseMove(arg);
	// float x = (float)arg.state.X.abs / (float)arg.state.width;
	// float y = (float)arg.state.Y.abs / (float)arg.state.height;
	
	// Ogre::Vector3 pt = InputListener::getInstance().getOgreManager().rayCast(x,y);
	// InputListener::getInstance().getConnection().move(pt);
	
	return true;
}
bool InputListener::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	// InputListener::getInstance().getCameraMan().injectMouseDown(arg,id);
	return true;
}
bool InputListener::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	// InputListener::getInstance().getCameraMan().injectMouseUp(arg, id);
	return true;
}