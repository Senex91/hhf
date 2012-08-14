#include "OgreManager.h"
#include "Client.h"
#include "Debug.h"

//-------------------------------------------------------------------------------------
OgreManager::OgreManager(void)
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    rayQuery(NULL),
    mCursorWasVisible(false),
    mShutDown(false)
{
}


void OgreManager::initialize() {
#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "cfg/resources.cfg";
	mPluginsCfg = "cfg/plugins.cfg";
#endif

	mRoot = new Ogre::Root(mPluginsCfg);

	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

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

	if(mRoot->restoreConfig()||mRoot->showConfigDialog()){
		// If returned true, user clicked OK so initialise
		// Here we choose to let the system create a default rendering window by passing 'true'
		mWindow = mRoot->initialise(true, "TutorialApplication Render Window");
	} else{ 
		return;
	}
		// Get the SceneManager, in this case a generic one
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
		// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");

	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0,0,80));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0,0,-300));
	mCamera->setNearClipDistance(5);

	// mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
	// mCameraMan->setStyle(OgreBites::CS_ORBIT);
	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Create any resource listeners (for loading screens)
	// createResourceListener();
	// Load resources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);
	
	rayQuery = mSceneMgr->createRayQuery(Ogre::Ray());
}

void OgreManager::destroy() {
	// destroyScene();
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	delete mRoot;
}

void OgreManager::update() {
	Ogre::WindowEventUtilities::messagePump();
	mRoot->renderOneFrame();
}


//-------------------------------------------------------------------------------------
OgreManager::~OgreManager(void) {
	
}
//-------------------------------------------------------------------------------------
bool OgreManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(mWindow->isClosed())
		return false;

	if(mShutDown)
		return false;

	return true;
}
//-------------------------------------------------------------------------------------
bool OgreManager::keyPressed( const OIS::KeyEvent &arg )
{
    // if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F)   // tuoggle visibility of advanced frame stats
    {
    }
    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
    {
        // if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        // {
        //     mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
        //     mDetailsPanel->show();
        // }
        // else
        // {
        //     mTrayMgr->removeWidgetFromTray(mDetailsPanel);
        //     mDetailsPanel->hide();
        // }
    }
    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    {
        // Ogre::String newVal;
        // Ogre::TextureFilterOptions tfo;
        // unsigned int aniso;

        // switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
        // {
        //     case 'B':
        //         newVal = "Trilinear";
        //         tfo = Ogre::TFO_TRILINEAR;
        //         aniso = 1;
        //         break;
        //     case 'T':
        //         newVal = "Anisotropic";
        //         tfo = Ogre::TFO_ANISOTROPIC;
        //         aniso = 8;
        //         break;
        //     case 'A':
        //         newVal = "None";
        //         tfo = Ogre::TFO_NONE;
        //         aniso = 1;
        //         break;
        //     default:
        //         newVal = "Bilinear";
        //         tfo = Ogre::TFO_BILINEAR;
        //         aniso = 1;
        // }

        // Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        // Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        // mDetailsPanel->setParamValue(9, newVal);
    }
    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
            case Ogre::PM_SOLID:
                newVal = "Wireframe";
                pm = Ogre::PM_WIREFRAME;
                break;
            case Ogre::PM_WIREFRAME:
                newVal = "Points";
                pm = Ogre::PM_POINTS;
                break;
            default:
                newVal = "Solid";
                pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
    }
    else if(arg.key == OIS::KC_F5)   // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }
    return true;
}

bool OgreManager::keyReleased( const OIS::KeyEvent &arg ) {
	return true;
}

bool OgreManager::mouseMoved( const OIS::MouseEvent &arg ) {
	return true;
}

bool OgreManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return true;
}

bool OgreManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return true;
}

//Adjust mouse clipping area
void OgreManager::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);
}

//Unattach OIS before window shutdown (very important under Linux)
void OgreManager::windowClosed(Ogre::RenderWindow* rw) {
	
}

Ogre::Vector3 OgreManager::rayCast(const float& x,const float& y) {
	Ogre::Ray r = mCamera->getCameraToViewportRay(x,y);
	Ogre::Plane p(Ogre::Vector3(0,1,0),0);
	std::pair<bool,float> pt = Ogre::Math::intersects(r,p);
	if(pt.first) {
		return r.getPoint(pt.second);
	} else {
		return Ogre::Vector3(0,0,0);
	}
	// return Ogre::Vector3(0,0,0);
}

Ogre::MovableObject* OgreManager::rayCastEntity(const float& x,const float& y,const Ogre::uint32& mask) {
	Ogre::Ray r = mCamera->getCameraToViewportRay(x,y);
	rayQuery->setRay(r);
	rayQuery->setQueryMask(mask);
	rayQuery->setSortByDistance(true,1); //1 result
	Ogre::RaySceneQueryResult results = rayQuery->execute();
	if(results.size()) { // != 0
		return results[0].movable;
	} else {
		return NULL;
	}
	// return Ogre::Vector3(0,0,0);
}

