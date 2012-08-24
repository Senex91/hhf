#include "CEGUIManager.h"
#include "Client.h"
#include "Util.h"
#include <string>
#include "UDPConnection.h"
#include "Debug.h"

using std::string;

CEGUIManager::CEGUIManager() {
	renderer = NULL;
	menuSheet = NULL;
	gameSheet = NULL;
}

CEGUIManager::~CEGUIManager() {
	
}

void CEGUIManager::initialize() {
	Ogre::RenderWindow* rw = Client::getInstance().getOgreManager().getWindow();
	renderer = &CEGUI::OgreRenderer::bootstrapSystem(*rw);
	OISManager& ois = Client::getInstance().getOISManager();
	ois.addKeyListener(this);
	ois.addMouseListener(this);
	
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("ASchemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	
	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	
	initializeMenuLayout();
	initializeGameLayout();
	CEGUI::System::getSingleton().setGUISheet(menuSheet);
	
	OgreManager& oi = Client::getInstance().getOgreManager();
	unsigned int width, height, depth;
	int left, top;
	oi.getWindow()->getMetrics(width, height, depth, left, top);
	
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Size(width, height));
	
	Ogre::WindowEventUtilities::addWindowEventListener(
		Client::getInstance().getOgreManager().getWindow(), this);
}

void CEGUIManager::destroy() {
	Ogre::WindowEventUtilities::removeWindowEventListener(
		Client::getInstance().getOgreManager().getWindow(), this);
	OISManager& ois = Client::getInstance().getOISManager();
	ois.removeKeyListener(this);
	ois.removeMouseListener(this);
	CEGUI::System::destroy();
	CEGUI::OgreRenderer::destroy(*renderer);
}

void CEGUIManager::initializeMenuLayout() {
	menuSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout("mainMenu.layout");
	try {
		CEGUI::Window* joinButton = CEGUI::WindowManager::getSingleton().getWindow("joinServerButton");
		if(joinButton) {
			joinButton->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&CEGUIManager::joinServer,this));
		}
	} catch(const CEGUI::Exception& e) {
		DEBUG("CEGUI Exception:");
		DEBUG(e.what());
	}
	menuSheet->setMousePassThroughEnabled(true);
}

void CEGUIManager::initializeGameLayout() {
	gameSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout("game.layout");
	gameSheet->setMousePassThroughEnabled(true);
}

bool CEGUIManager::joinServer(const CEGUI::EventArgs&) {
	CEGUI::System::getSingleton().setGUISheet(menuSheet);
	try {
		CEGUI::Window* serverBox = CEGUI::WindowManager::getSingleton().getWindow("ServerBox");
		CEGUI::Window* portBox = CEGUI::WindowManager::getSingleton().getWindow("PortBox");
		if(!serverBox || !portBox) { return false; }
		string hostname = string(serverBox->getText().c_str());
		unsigned int port = fromString<unsigned int>(string(portBox->getText().c_str()));
		Client::getInstance().getNetServer().joinServer(Address(hostname,port));
		CEGUI::System::getSingleton().setGUISheet(gameSheet);
		return true;
	} catch(const CEGUI::Exception& e) {
		DEBUG("CEGUI Exception:");
		DEBUG(e.what());
	}
	return false;
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

void CEGUIManager::windowResized(Ogre::RenderWindow* rw) {
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Size(width,height));
	DEBUG("Display size changed");
}