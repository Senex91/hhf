#ifndef OGRE_MANAGER_H
#define OGRE_MANAGER_H

#include <Ogre.h>

#include "TOCameraMan.h"

class OgreManager: public Ogre::FrameListener{
public:
	OgreManager();
	~OgreManager();
	
	void initialize();
	void destroy();
	
	void update();
	
	// Ogre::Vector3 rayCast(const float& x,const float& y);
	
	Ogre::Root* getRoot() { return root; }
	Ogre::Camera* getCamera() { return camera; }
	Ogre::SceneManager* getSceneManager() { return sceneManager; }
	Ogre::RenderWindow* getWindow() { return window; }


	// virtual bool setup();
 //    virtual bool configure(void);
 //    virtual void chooseSceneManager(void);
 //    virtual void createCamera(void);
 //    virtual void createFrameListener(void);
 //    virtual void createScene(void) = 0; // Override me!
 //    virtual void destroyScene(void);
 //    virtual void createViewports(void);
 //    virtual void setupResources(void);
 //    virtual void createResourceListener(void);
 //    virtual void loadResources(void);

protected:

	   // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
private:
	Ogre::Root *root;
	Ogre::Camera* camera;
	Ogre::SceneManager* sceneManager;
	Ogre::RenderWindow* window;
	Ogre::String resourcesCfg;
	Ogre::String pluginsCfg;
	// Ogre::RaySceneQuery* raySceneQuery;

	// // Ogre::WindowEventListener
 //    //Adjust mouse clipping area
 //    virtual void windowResized(Ogre::RenderWindow* rw);
 //    //Unattach OIS before window shutdown (very important under Linux)
 //    virtual void windowClosed(Ogre::RenderWindow* rw);

 //    Ogre::Root *mRoot;
 //    Ogre::Camera* mCamera;
 //    Ogre::SceneManager* mSceneMgr;
 //    Ogre::RenderWindow* mWindow;
 //    Ogre::String mResourcesCfg;
 //    Ogre::String mPluginsCfg;

 //    // OgreBites
 //    OgreBites::SdkTrayManager* mTrayMgr;
 //    OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller
 //    OgreBites::ParamsPanel* mDetailsPanel;     // sample details panel
 //    bool mCursorWasVisible;                    // was cursor visible before dialog appeared
 //    bool mShutDown;
};

#endif