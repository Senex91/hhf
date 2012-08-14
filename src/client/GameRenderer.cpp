#include "GameRenderer.h"

#include <Ogre.h>


#include "Debug.h"
#include "Client.h"

#include "OgreElf.h"

#include <cmath>

GameRenderer::GameRenderer(){

}

GameRenderer::~GameRenderer(){

}

void GameRenderer::initialize(){
	
	DEBUG("GameRenderer::initialize");
	
	Client::getInstance().getOgreManager().getRoot()->addFrameListener(this);
	
	// Tray manager, hacky fix for intel graphics
	mTrayMgr = new OgreBites::SdkTrayManager(
		"InterfaceName", 
		Client::getInstance().getOgreManager().getWindow(), 
		Client::getInstance().getOISManager().getMouse(), 
		this);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	mTrayMgr->toggleAdvancedFrameStats();
	mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
	mTrayMgr->hideCursor();
	
	//cameraMan = new OgreBites::SdkCameraMan(Client::getInstance().getOgreManager().getCamera());
	Client::getInstance().getOISManager().addMouseListener(this);
	Client::getInstance().getOISManager().addKeyListener(this);
	
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	
	Ogre::Entity* entGround = 
		Client::getInstance()
			.getOgreManager()
			.getSceneManager()
			->createEntity("GroundEntity", "ground");

	Ogre::SceneNode* groundNode = Client::getInstance().getOgreManager().getSceneManager()->getRootSceneNode()->createChildSceneNode();
	groundNode->attachObject(entGround);
	groundNode->scale(.1, .1, .1);
	
	entGround->setMaterialName("Examples/Rockwall");
	entGround->setCastShadows(false);
	entGround->setQueryFlags(0);
	
	//point light
	Ogre::Light* pointLight = Client::getInstance().getOgreManager().getSceneManager()->createLight("pointLight");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(Ogre::Vector3(0, 10, 10));
	pointLight->setDiffuseColour(1.0, 1.0, 1.0);
	pointLight->setSpecularColour(1.0, 1.0, 1.0);
	
	Client::getInstance()
		.getOgreManager()
		.getSceneManager()
		->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	
	orb = new OgreOrb(Client::getInstance().getOgreManager().getSceneManager());
	felhound = new OgreFelhound(Client::getInstance().getOgreManager().getSceneManager(),0);
	
	cameraStyles["TOCameraMan"] = new TOCameraManStyle();
	cameraStyles["WC3Style"] = new WC3CameraStyle();
	cameraStyles["WC3Style"]->load();
	
	DEBUG("GameRenderer::initialize done");
}

void GameRenderer::destroy() {
	Client::getInstance().getOISManager().removeMouseListener(this);
	Client::getInstance().getOISManager().removeKeyListener(this);
	for(std::map<int,OgreElf*>::iterator it = elves.begin(); it != elves.end(); it++) {
		delete it->second;
	}
	elves.clear();
	delete orb;
}

void GameRenderer::renderNextState(GameState const& newState){
	for(unsigned int i = 0; i < newState.elves.size(); i++){
		
		const Elf& elfState = newState.elves[i];
		int elfID = elfState.id;

		OgreElf* current = NULL;

		// ALLOCATE OGRE ELF
		if (elves.count(elfID)){ // if elf exists
			current = elves[elfID];
		} else{ // Current elf doesn't exists
			current = new OgreElf(
				Client::getInstance().getOgreManager().getSceneManager(),
				Ogre::ColourValue(elfState.color.r, elfState.color.g, elfState.color.b),
				elfID);
			elves[elfID] = current;
		}

		current->setPosition(elfState.x, 0, elfState.y);
		current->setOrientation(elfState.orientation);
	}
	orb->setPosition(newState.orb.x,2,newState.orb.y);
	felhound->setPosition(newState.felhound.x, 0, newState.felhound.y);
	felhound->setOrientation(newState.felhound.orientation);

}



// OIS::KeyListener
bool GameRenderer::keyPressed( const OIS::KeyEvent &arg ) {
	return true;
}

bool GameRenderer::keyReleased( const OIS::KeyEvent &arg ) {
	return true;
}

// OIS::MouseListener
bool GameRenderer::mouseMoved( const OIS::MouseEvent &arg ) {
	return true;
}

bool GameRenderer::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return true;
}

bool GameRenderer::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return true;
}

bool GameRenderer::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	mTrayMgr->frameRenderingQueued(evt);
	return true;
}