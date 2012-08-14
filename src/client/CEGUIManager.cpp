#include "CEGUIManager.h"
#include "Client.h"

CEGUIManager::CEGUIManager() {
	
}

CEGUIManager::~CEGUIManager() {
	
}

void CEGUIManager::initialize() {
	Ogre::RenderWindow* rw = Client::getInstance().getOgreManager().getWindow();
	renderer = &CEGUI::OgreRenderer::bootstrapSystem(*rw);
	OISManager& ois = Client::getInstance().getOISManager();
	ois.addKeyListener(this);
	ois.addMouseListener(this);
}

void CEGUIManager::destroy() {
	OISManager& ois = Client::getInstance().getOISManager();
	ois.removeKeyListener(this);
	ois.removeMouseListener(this);
	CEGUI::System::destroy();
	CEGUI::OgreRenderer::destroy(*renderer);
}

// OIS::KeyListener
bool CEGUIManager::keyPressed( const OIS::KeyEvent &arg ) { //TODO: key repeating based on frames
	bool a = CEGUI::System::getSingleton().injectKeyDown(arg.key);
	bool b = CEGUI::System::getSingleton().injectChar(arg.text);
	return a || b; // I save these to variables so that the short-circuiting doesn't happen
}

bool CEGUIManager::keyReleased( const OIS::KeyEvent &arg ) {
	return CEGUI::System::getSingleton().injectKeyUp(arg.key);
}

// OIS::MouseListener

CEGUI::MouseButton oisToCEGUIMouseButton(const OIS::MouseButtonID& id) {
	CEGUI::MouseButton mb = CEGUI::NoButton;
	switch(id) {
		case OIS::MB_Left:
			mb = CEGUI::LeftButton;
			break;
		case OIS::MB_Right:
			mb = CEGUI::RightButton;
			break;
		case OIS::MB_Middle:
			mb = CEGUI::MiddleButton;
			break;
		case OIS::MB_Button3:
			mb = CEGUI::X1Button;
			break;
		case OIS::MB_Button4:
			mb = CEGUI::X2Button;
			break;
		case OIS::MB_Button5:
			
			break;
		case OIS::MB_Button6:
			
			break;
		case OIS::MB_Button7:
			
			break;
	}
	return mb;
}

bool CEGUIManager::mouseMoved( const OIS::MouseEvent &arg ) {
	return CEGUI::System::getSingleton().injectMousePosition(arg.state.X.abs,arg.state.Y.abs);
}

bool CEGUIManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return CEGUI::System::getSingleton().injectMouseButtonDown(oisToCEGUIMouseButton(id));
}
bool CEGUIManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return CEGUI::System::getSingleton().injectMouseButtonUp(oisToCEGUIMouseButton(id));
}