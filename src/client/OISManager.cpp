#include "OISManager.h"
#include "Client.h"

#include "Debug.h"

OISManager::OISManager(){
	inputManager = NULL;
	mouse = NULL;
	keyboard = NULL;
}

OISManager::~OISManager() {
	
}

void OISManager::initialize() {
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	Client::getInstance().getOgreManager().getWindow()->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));


	inputManager = OIS::InputManager::createInputSystem( pl );

	keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject( OIS::OISKeyboard, true ));
	mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject( OIS::OISMouse, true ));

	mouse->setEventCallback(this);
	keyboard->setEventCallback(this);
	
	unsigned int width, height, depth;
    int left, top;
    Client::getInstance().getOgreManager().getWindow()->getMetrics(width, height, depth, left, top);
 
    const OIS::MouseState &ms = mouse->getMouseState();
    ms.width = width;
    ms.height = height;
    DEBUG("!!!!!!!!!!! OIS INITIATE DONE !!!!!!!!!!!");
}

void OISManager::destroy() {
	inputManager->destroyInputObject( mouse );
	inputManager->destroyInputObject( keyboard );

	OIS::InputManager::destroyInputSystem(inputManager);
	inputManager = 0;
}

void OISManager::update() {
	keyboard->capture();
	mouse->capture();
}

// OIS::KeyListener
bool OISManager::keyPressed( const OIS::KeyEvent &arg ) {
	// Client::getInstance().getCameraMan().injectKeyDown(arg);
	DEBUG("Key Pressed" <<arg.key);
	return true;
}
bool OISManager::keyReleased( const OIS::KeyEvent &arg ) {
	if(arg.key == OIS::KC_F12) {
		// Client::getInstance().setRunning(false);
	}
	// Client::getInstance().getCameraMan().injectKeyUp(arg);
	DEBUG("Key released" << arg.key);
	return true;
}
// OIS::MouseListener
bool OISManager::mouseMoved( const OIS::MouseEvent &arg ) {
	DEBUG("mouse move");
	// Client::getInstance().getCameraMan().injectMouseMove(arg);
	float x = (float)arg.state.X.abs / (float)arg.state.width;
	float y = (float)arg.state.Y.abs / (float)arg.state.height;
	
	// Ogre::Vector3 pt = Client::getInstance().getOgreManager().rayCast(x,y);
	// Client::getInstance().getConnection().move(pt);
	
	return true;
}
bool OISManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	// Client::getInstance().getCameraMan().injectMouseDown(arg,id);
	return true;
}
bool OISManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	// Client::getInstance().getCameraMan().injectMouseUp(arg, id);
	return true;
}