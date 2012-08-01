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
};

#endif