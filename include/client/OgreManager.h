#ifndef OGRE_MANAGER_H
#define OGRE_MANAGER_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <OgreRenderSystem.h>
#include <OgreWindowEventUtilities.h>
#include <OgreManualObject.h>

#include "TOCameraMan.h"

#include <SdkTrays.h>

class OgreManager: 
	public Ogre::FrameListener, 
	public Ogre::WindowEventListener,
	public OIS::KeyListener, 
	public OIS::MouseListener,
	OgreBites::SdkTrayListener {
public:
	OgreManager();
	~OgreManager();
	
	void initialize();
	void destroy();
	
	void update();
	
	Ogre::Vector3 rayCast(const float& x,const float& y);
	Ogre::MovableObject* rayCastEntity(const float& x,const float& y,const Ogre::uint32& mask = -1);
	
	Ogre::Root* getRoot() { return mRoot; }
	Ogre::Camera* getCamera() { return mCamera; }
	Ogre::SceneManager* getSceneManager() { return mSceneMgr; }
	Ogre::RenderWindow* getWindow() { return mWindow; }
	
protected:
	// Ogre::FrameListener
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
	// // OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	
	// Ogre::WindowEventListener
	//Adjust mouse clipping area
	virtual void windowResized(Ogre::RenderWindow* rw);
	//Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(Ogre::RenderWindow* rw);
	
	Ogre::Root *mRoot;
	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	
	Ogre::RaySceneQuery* rayQuery;
	bool mCursorWasVisible;                    // was cursor visible before dialog appeared
	bool mShutDown;
private:
	
};

#endif