#ifndef CAMERA_STYLE_H
#define CAMERA_STYLE_H

#include <OgreCamera.h>
#include <GLX/OgreTimerImp.h>
#include <TOCameraMan.h>

class CameraStyle : public OIS::KeyListener, public OIS::MouseListener, public Ogre::FrameListener {
public:
	CameraStyle();
	virtual ~CameraStyle();
	
	virtual void load();
	virtual void unload();
	
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg ) = 0;
	virtual bool keyReleased( const OIS::KeyEvent &arg ) = 0;
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg ) = 0;
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) = 0;
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) = 0;
	
protected:
	// Ogre::FrameListener
	bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;
	
	virtual void innerLoad() {}
	virtual void innerUnload() {}
	
	Ogre::Camera* camera;
	OIS::Mouse* mouse;
	OIS::Keyboard* keyboard;
};

class TOCameraManStyle : public CameraStyle {
public:
	TOCameraManStyle();
	virtual ~TOCameraManStyle();
	
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	
protected:
	virtual void innerLoad();
	virtual void innerUnload();
	// Ogre::FrameListener
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
private:
	OgreBites::SdkCameraMan* cameraMan;
};

class WC3CameraStyle : public CameraStyle {
public:
	WC3CameraStyle();
	virtual ~WC3CameraStyle();
	
	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	
	static const int scrollThreshold = 10;
	static const float scrollSpeed = 1;
	
protected:
	virtual void innerLoad();
	virtual void innerUnload();
	
	// Ogre::FrameListener
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	Ogre::Timer timer;
};

#endif