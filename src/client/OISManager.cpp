#include "OISManager.h"
#include "Client.h"

#include "Debug.h"

OISManager::OISManager(): mouseListeners(), keyListeners(){
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
	
	// unsigned int width, height, depth;
 //    int left, top;
 //    Client::getInstance().getOgreManager().getWindow()->getMetrics(width, height, depth, left, top);
	windowResized(
		Client::getInstance().getOgreManager().getWindow());
    Ogre::WindowEventUtilities::addWindowEventListener(
    	Client::getInstance().getOgreManager().getWindow(), this);
 
    
    DEBUG("!!!!!!!!!!! OIS INITIATE DONE !!!!!!!!!!!");
}

void OISManager::destroy() {
	Ogre::WindowEventUtilities::removeWindowEventListener(
		Client::getInstance().getOgreManager().getWindow(), this);
	inputManager->destroyInputObject( mouse );
	inputManager->destroyInputObject( keyboard );

	OIS::InputManager::destroyInputSystem(inputManager);
	inputManager = 0;
}

void OISManager::update() {
	keyboard->capture();
	mouse->capture();
}
//Adjust mouse clipping area
void OISManager::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);
	const OIS::MouseState &ms = mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void OISManager::addMouseListener(OIS::MouseListener* listener){
	mouseListeners.insert(listener);
}

void OISManager::addKeyListener(OIS::KeyListener* listener){
	keyListeners.insert(listener);
}

void OISManager::removeMouseListener(OIS::MouseListener* listener){
	mouseListeners.erase(listener);
}

void OISManager::removeKeyListener(OIS::KeyListener* listener){
	keyListeners.erase(listener);
}

// OIS::KeyListener
bool OISManager::keyPressed( const OIS::KeyEvent &arg ) {
	for(std::set<OIS::KeyListener*>::iterator it = keyListeners.begin(); 
		it !=keyListeners.end(); it++){
		(*it)->keyPressed(arg);
	}
	return true;
}

bool OISManager::keyReleased( const OIS::KeyEvent &arg ) {
	for(std::set<OIS::KeyListener*>::iterator it = keyListeners.begin(); 
		it !=keyListeners.end(); it++){
		(*it)->keyReleased(arg);
	}
	return true;
}

// OIS::MouseListener
bool OISManager::mouseMoved( const OIS::MouseEvent &arg ) {
	for(std::set<OIS::MouseListener*>::iterator it = mouseListeners.begin(); 
		it !=mouseListeners.end(); it++){
		(*it)->mouseMoved(arg);
	}
	return true;
}

bool OISManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	for(std::set<OIS::MouseListener*>::iterator it = mouseListeners.begin(); 
		it !=mouseListeners.end(); it++){
		(*it)->mousePressed(arg,id);
	}
	return true;
}

bool OISManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	for(std::set<OIS::MouseListener*>::iterator it = mouseListeners.begin(); 
		it !=mouseListeners.end(); it++){
		(*it)->mouseReleased(arg,id);
	}
	return true;
}