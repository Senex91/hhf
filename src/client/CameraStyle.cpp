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
	innerLoad();
}

void CameraStyle::unload() {
	Client::getInstance().getOISManager().removeMouseListener(this);
	Client::getInstance().getOISManager().removeKeyListener(this);
	Client::getInstance().getOgreManager().getRoot()->removeFrameListener(this);
	innerUnload();
}

TOCameraManStyle::TOCameraManStyle() {
	cameraMan = NULL;
}

TOCameraManStyle::~TOCameraManStyle() {
	if(cameraMan) {
		delete cameraMan;
	}
}

void TOCameraManStyle::innerLoad() {
	cameraMan = new OgreBites::SdkCameraMan(camera);
}

void TOCameraManStyle::innerUnload() {
	delete cameraMan;
	cameraMan = NULL;
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
	cameraMan->frameRenderingQueued(evt);
	return true;
}

const int WC3CameraStyle::scrollThreshold;
const float WC3CameraStyle::scrollSpeed;

WC3CameraStyle::WC3CameraStyle() {
	
}

WC3CameraStyle::~WC3CameraStyle() {
	
}

void WC3CameraStyle::innerLoad() {
	camera->setPosition(Ogre::Vector3(0,100,0));
	camera->lookAt(Ogre::Vector3(0,0,0));
}

void WC3CameraStyle::innerUnload() {
	
}

//OIS::KeyListener
bool WC3CameraStyle::keyPressed( const OIS::KeyEvent &arg ) {
	
	return true;
}

bool WC3CameraStyle::keyReleased( const OIS::KeyEvent &arg ) {
	
	return true;
}

// OIS::MouseListener
bool WC3CameraStyle::mouseMoved( const OIS::MouseEvent &arg ) {
	
	return true;
}
bool WC3CameraStyle::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	
	return true;
}
bool WC3CameraStyle::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	
	return true;
}

bool WC3CameraStyle::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	using Ogre::Vector3;
	//TODO: timers
	Vector3 camPos = camera->getPosition();
	const OIS::MouseState& state = mouse->getMouseState();
	
	if(state.X.abs < scrollThreshold) {
		camPos -= Vector3(scrollSpeed,0,0);
	} else if(state.X.abs > state.width - scrollThreshold) {
		camPos += Vector3(scrollSpeed,0,0);
	}
	
	if(state.Y.abs < scrollThreshold) {
		camPos -= Vector3(0,0,scrollSpeed);
	} else if(state.Y.abs > state.height - scrollThreshold) {
		camPos += Vector3(0,0,scrollSpeed);
	}
	
	camera->setPosition(camPos);
	
	return true;
}