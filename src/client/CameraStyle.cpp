#include "CameraStyle.h"
#include "Client.h"

CameraStyle::CameraStyle() {
	camera = Client::getInstance().getOgreManager().getCamera();
	mouse = Client::getInstance().getOISManager().getMouse();
	keyboard = Client::getInstance().getOISManager().getKeyboard();
}

CameraStyle::~CameraStyle() {
	//The CameraStyle is not the owner of the pointers it holds, so they are not deleted.
}

void CameraStyle::load() {
	Client::getInstance().getOISManager().addMouseListener(this);
	Client::getInstance().getOISManager().addKeyListener(this);
	Client::getInstance().getOgreManager().getRoot()->addFrameListener(this);
}

void CameraStyle::unload() {
	Client::getInstance().getOISManager().removeMouseListener(this);
	Client::getInstance().getOISManager().removeKeyListener(this);
	Client::getInstance().getOgreManager().getRoot()->removeFrameListener(this);
}

TOCameraManStyle::TOCameraManStyle() {
	cameraMan = new OgreBites::SdkCameraMan(camera);
}

TOCameraManStyle::~TOCameraManStyle() {
	delete cameraMan;
}

//OIS::KeyListener
bool TOCameraManStyle::keyPressed( const OIS::KeyEvent &arg ) {
	cameraMan->injectKeyDown(arg);
	return true;
}

bool TOCameraManStyle::keyReleased( const OIS::KeyEvent &arg ) {
	cameraMan->injectKeyUp(arg);
	return true;
}

// OIS::MouseListener
bool TOCameraManStyle::mouseMoved( const OIS::MouseEvent &arg ) {
	cameraMan->injectMouseMove(arg);
	return true;
}
bool TOCameraManStyle::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	cameraMan->injectMouseDown(arg,id);
	return true;
}
bool TOCameraManStyle::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	cameraMan->injectMouseUp(arg, id);
	return true;
}

bool TOCameraManStyle::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	cameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
	return true;
}