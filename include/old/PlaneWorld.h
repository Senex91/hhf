
#ifndef __PlaneWorld_h_
#define __PlaneWorld_h_

#include "BaseApplication.h"
#include "Axes.h"
#include <vector>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

class PlaneWorld : public BaseApplication{
public:
    PlaneWorld(void);
    virtual ~PlaneWorld(void);

protected:

    CEGUI::OgreRenderer* mRenderer;

    virtual void createScene(void);

    bool quit(const CEGUI::EventArgs &e);
    bool positionSliderMoved(const CEGUI::EventArgs &e);
    bool speedSliderMoved(const CEGUI::EventArgs &e);

    Axes* axe;

    virtual void createFrameListener(void);

    // Ogre::WindowEventListener
    //Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

private:
    CEGUI::MouseButton convertButton(OIS::MouseButtonID);

};

#endif // #ifndef __PlaneWorld_h_
