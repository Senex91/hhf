#include "OISManager.h"
#include "Client.h"

#include "Debug.h"

OISManager::OISManager(): listeners(){
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

void OISManager::addInputListener(InputListener* listener){
	listeners.insert(listener);
}

void OISManager::removeInputListener(InputListener* listener){
	listeners.erase(listener);
}
// OIS::KeyListener
bool OISManager::keyPressed( const OIS::KeyEvent &arg ) {
	for(std::set<InputListener*>::iterator it = listeners.begin(); 
		it !=listeners.end(); it++){
		(*it)->keyPressed(arg);
	}
	return true;
}
bool OISManager::keyReleased( const OIS::KeyEvent &arg ) {
	for(std::set<InputListener*>::iterator it = listeners.begin(); 
		it !=listeners.end(); it++){
		(*it)->keyReleased(arg);
	}
	return true;
}
// OIS::MouseListener
bool OISManager::mouseMoved( const OIS::MouseEvent &arg ) {
	for(std::set<InputListener*>::iterator it = listeners.begin(); 
		it !=listeners.end(); it++){
		(*it)->mouseMoved(arg);
	}
	return true;
}
bool OISManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	for(std::set<InputListener*>::iterator it = listeners.begin(); 
		it !=listeners.end(); it++){
		(*it)->mousePressed(arg,id);
	}
	return true;
}
bool OISManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	for(std::set<InputListener*>::iterator it = listeners.begin(); 
		it !=listeners.end(); it++){
		(*it)->mouseReleased(arg,id);
	}
	return true;
}