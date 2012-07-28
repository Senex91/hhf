#include "OgreManager.h"
#include "Game.h"

OgreManager::OgreManager(Game& game) : game(game) {
	
}

OgreManager::~OgreManager() {
	
}

void OgreManager::initialize() {
	resourcesCfg = "cfg/resources.cfg";
	pluginsCfg = "cfg/plugins.cfg";
	
	// construct Ogre::Root
	root = new Ogre::Root(pluginsCfg);
	
	//-------------------------------------------------------------------------------------
	// setup resources
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(resourcesCfg);
	
	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
	//-------------------------------------------------------------------------------------
	// configure
	//-------------------------------------------------------------------------------------
	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if(root->restoreConfig() || root->showConfigDialog())
	{
		// If returned true, user clicked OK so initialise
		// Here we choose to let the system create a default rendering window by passing 'true'
		window = root->initialise(true, "Court Ichiro");
	}
	else
	{
		return;
	}
	//-------------------------------------------------------------------------------------
	// choose scenemanager
	// Get the SceneManager, in this case a generic one
	sceneManager = root->createSceneManager(Ogre::ST_GENERIC);
	//-------------------------------------------------------------------------------------
	// create camera
	// Create the camera
	camera = sceneManager->createCamera("PlayerCam");
	
	// Position it at 500 in Z direction
	camera->setPosition(Ogre::Vector3(0,0,80));
	// Look back along -Z
	camera->lookAt(Ogre::Vector3(0,0,-300));
	camera->setNearClipDistance(5);
	//-------------------------------------------------------------------------------------
	// create viewports
	// Create one viewport, entire window
	Ogre::Viewport* vp = window->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	
	// Alter the camera aspect ratio to match the viewport
	camera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	//-------------------------------------------------------------------------------------
	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//-------------------------------------------------------------------------------------
	// load resources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	//-------------------------------------------------------------------------------------
	sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

void OgreManager::destroy() {
	delete root;
}

void OgreManager::update() {
	root->renderOneFrame();
}