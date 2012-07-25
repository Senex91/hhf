
#include "PlaneWorld.h"
#include <iostream>
#include <vector>

#define NORMAL_MODE 0


//-------------------------------------------------------------------------------------
PlaneWorld::PlaneWorld(void){
    //PlaneWorld::PlaneWorld(void){
}
//-------------------------------------------------------------------------------------
PlaneWorld::~PlaneWorld(void){

    CEGUI::OgreRenderer::destroySystem();

}
void loadGrid(Ogre::SceneManager* mSceneMgr, int numcols, int numrows, float unitsize){
    Ogre::ManualObject* grid = mSceneMgr->createManualObject("grid");    

    grid->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);

    float width = (float)numcols * unitsize;
    float depth = (float)numrows * unitsize;
    Ogre::Vector3 center = Ogre::Vector3((-width / 2.0f), 0 ,( -depth / 2.0f));

    Ogre::ColourValue white = Ogre::ColourValue(1.0f, 1.0f, 1.0f, 0.5f); 
    int count = 0;
    for (int i = 0; i < numrows; ++i)
    {   
        Ogre::Vector3 s, e;
        s.x = 0.0f;
        s.z = i * unitsize; s.y = 0.0f;

        e.x = width;
        e.z = i * unitsize;
        e.y = 0.0f;

        grid->position(s + center);
        grid->colour(white);
        grid->position(e + center);
        grid->colour(white);
        grid->index(count++);
        grid->index(count++);
    }   
    grid->position(Ogre::Vector3(0.0f, 0.0f, numrows * unitsize) + center);
    grid->colour(white);
    grid->position(Ogre::Vector3(width, 0.0f, numrows * unitsize) + center);
    grid->colour(white);
    grid->index(count++);
    grid->index(count++);

    for (int i = 0; i < numcols; ++i)
    {   
        Ogre::Vector3 s, e;
        s.x = i * unitsize;
        s.z = depth;
        s.y = 0.0f;

        e.x = i * unitsize;
        e.z = 0.0f;
        e.y = 0.0f;

        grid->position(s + center);
        grid->colour(white);
        grid->position(e + center);
        grid->colour(white);
        grid->index(count++);
        grid->index(count++);
    }   
    grid->position(Ogre::Vector3(numcols * unitsize, 0.0f, 0.0f) + center);
    grid->colour(white);
    grid->position(Ogre::Vector3(numcols * unitsize, 0.0f, depth) + center);
    grid->colour(white);
    grid->index(count++);
    grid->index(count++);
    grid->end();

    Ogre::String meshName= "Grid";
    Ogre::String lResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
    grid->convertToMesh(meshName); 
}

void loadPath(Ogre::SceneManager* mSceneMgr){
    Ogre::ManualObject* lManualObject = NULL;
    {
        Ogre::String lManualObjectName = "CubeWithAxes";
        lManualObject = mSceneMgr->createManualObject(lManualObjectName);

        // Always tell if you want to update the 3D (vertex/index) later or not.
        bool lDoIWantToUpdateItLater = false;
        lManualObject->setDynamic(lDoIWantToUpdateItLater);

    }
    std::vector<Ogre::Vector3> path;
    path.push_back(Ogre::Vector3(0,0,1));
    path.push_back(Ogre::Vector3(2,0,2));
    path.push_back(Ogre::Vector3(3,0,4));
    path.push_back(Ogre::Vector3(4,0,6));
    path.push_back(Ogre::Vector3(5,0,8));

    lManualObject->begin("BaseWhiteNoLighting",Ogre::RenderOperation::OT_POINT_LIST);
    {

        int indexes = 0;
        for(int i = 1; i<path.size(); i++){

            std::cout <<" index " << i << std::endl;
            Ogre::Vector3 c,v,a,b;
            c.x = path[i - 1].x;
            c.y = path[i - 1].y;
            c.z = path[i - 1].z;

            v.x = path[i].x - path[i - 1].x;
            v.y = path[i].y - path[i - 1].y;
            v.z = path[i].z - path[i - 1].z;
            v.normalise();

            a = v.perpendicular();
            b = a.crossProduct(v);


            lManualObject->position(c);
            lManualObject->colour(Ogre::ColourValue::Red);
            lManualObject->index(indexes++);

            lManualObject->position(v);
            lManualObject->colour(Ogre::ColourValue::Red);
            lManualObject->index(indexes++);

            lManualObject->position(a);
            lManualObject->colour(Ogre::ColourValue::Green);
            lManualObject->index(indexes++);

            lManualObject->position(b);
            lManualObject->colour(Ogre::ColourValue::Blue);
            lManualObject->index(indexes++);

            for(float theta = 0; theta < Ogre::Math::TWO_PI; theta+=0.1){
                Ogre::Vector3 pos;
                pos.x = c.x + cos(theta) * a.x + sin(theta)*b.x;
                pos.y = c.y + cos(theta) * a.y + sin(theta)*b.y;
                pos.z = c.z + cos(theta) * a.z + sin(theta)*b.z;
                lManualObject->position(pos);
                lManualObject->colour(1, 1, 0);
                lManualObject->index(indexes++);

            }




        }

    }
    lManualObject->end();
    Ogre::String lNameOfTheMesh = "MeshCubeAndAxe";
    Ogre::String lResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
    lManualObject->convertToMesh(lNameOfTheMesh);

    Ogre::Entity* lEntity = mSceneMgr->createEntity(lNameOfTheMesh);
    Ogre::SceneNode* lNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    lNode->attachObject(lEntity);
}




//-------------------------------------------------------------------------------------
void PlaneWorld::createScene(void){


    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();


    CEGUI::SchemeManager::getSingleton().create("WindowsLook.scheme");

    //CEGUI::System::getSingleton().setDefaultMouseCursor("WindowsLook", "MouseArrow");

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window* sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    CEGUI::Window* quit = wmgr.createWindow("WindowsLook/Button", "CEGUIDemo/QuitButton");
    quit->setText("Quit");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));

    //sheet->addChildWindow(quit);
    CEGUI::System::getSingleton().setGUISheet(sheet);


    quit->subscribeEvent(CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&PlaneWorld::quit, this));


#if NORMAL_MODE

    /*
       CEGUI::Window* slider = wmgr.createWindow("WindowsLook/Slider", "CEGUIDemo/PlaySlider");
       slider->setSize(CEGUI::UVector2(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
       slider->subscribeEvent(
       CEGUI::Slider::EventValueChanged,
       CEGUI::Event::Subscriber(&PlaneWorld::sliderMoved, this));
       */
    CEGUI::Slider * positionSlider= static_cast<CEGUI::Slider*>(wmgr.createWindow("WindowsLook/Slider", "PositionSlider"));
    sheet->addChildWindow(positionSlider);
    positionSlider->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0,0), CEGUI::UDim(0.0,0)));
    positionSlider->setMaxValue(1.0f);
    positionSlider->setClickStep(0.1f);
    positionSlider->setCurrentValue(0.0f); // Start half way

    positionSlider->subscribeEvent(
            CEGUI::Slider::EventValueChanged, 
            CEGUI::Event::Subscriber(
                &PlaneWorld::positionSliderMoved, 
                this));


    sheet->addChildWindow(positionSlider);

    CEGUI::Slider * speedSlider= static_cast<CEGUI::Slider*>(wmgr.createWindow("WindowsLook/Slider", "SpeedSlider"));
    sheet->addChildWindow(speedSlider);
    speedSlider->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0,0), CEGUI::UDim(0.80,0)));
    speedSlider->setSize(CEGUI::UVector2(CEGUI::UDim(0.90,0), CEGUI::UDim(0.04,0)));
    speedSlider->setMaxValue(40.0f);
    speedSlider->setClickStep(0.1f);
    speedSlider->setCurrentValue(5.0f); // Start half way

    speedSlider->subscribeEvent(
            CEGUI::Slider::EventValueChanged, 
            CEGUI::Event::Subscriber(
                &PlaneWorld::speedSliderMoved, 
                this));

    sheet->addChildWindow(speedSlider);

#endif

    loadGrid(mSceneMgr, 100, 100, 3.0f);

    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));


    //point light
    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight-> setPosition(Ogre::Vector3(0, 10, 10));
    pointLight->setDiffuseColour(1.0, 1.0, 1.0);
    pointLight->setSpecularColour(1.0, 1.0, 1.0);

    Ogre::Entity* grid = mSceneMgr->createEntity("Grid");
    Ogre::SceneNode* gridNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GridNode");
    gridNode->attachObject(grid);

    Ogre::MaterialPtr gridMat = grid->getSubEntity(0)->getMaterial();
    gridMat->getTechnique(0)->getPass(0)->setAmbient(Ogre::ColourValue(.5, .5, .5, 0));
    gridMat->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(.5, .5, .5, 0));
    grid->setMaterialName(gridMat->getName());


    /*
       Axes::loadMesh(mSceneMgr, 1);
       axe = new Axes(mRoot, mSceneMgr, "0");
       axe->setPosition(0,0,0);
       axe->setHeading(0);
       */
    Ogre::SceneNode* cameraNode= mSceneMgr->getRootSceneNode()->createChildSceneNode("cameraNode");
    mCameraMan->setTarget(cameraNode);
    Axes::loadMesh(mSceneMgr, 1);
    Ogre::Entity* orbitAxes = mSceneMgr->createEntity("orbitAxes", "MeshAxe");
    //Ogre::Entity* orbitAxes = mSceneMgr->createEntity("orbitAxes", "sphere.mesh");
    //cameraNode->attachObject(orbitAxes);
    mCameraMan->setTarget(cameraNode, orbitAxes );


    loadPath(mSceneMgr);



}

void PlaneWorld::createFrameListener(void){
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
#if defined OIS_WIN32_PLATFORM
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard,    true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mRoot->addFrameListener(this);
}

bool PlaneWorld::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

    return true;
}

bool PlaneWorld::keyPressed( const OIS::KeyEvent &arg )
{
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(arg.key);
    sys.injectChar(arg.text);

    if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

    mCameraMan->injectKeyDown(arg);
    return true;
}

bool PlaneWorld::keyReleased( const OIS::KeyEvent &arg )
{
    //if(CEGUI::System::getSingleton().injectKeyUp(arg.key)) return true;
    CEGUI::System::getSingleton().injectKeyUp(arg.key);
    mCameraMan->injectKeyUp(arg);
    return true;
}

CEGUI::MouseButton PlaneWorld::convertButton(OIS::MouseButtonID buttonID){
    switch (buttonID)
    {
        case OIS::MB_Left:
            return CEGUI::LeftButton;
            break;

        case OIS::MB_Right:
            return CEGUI::RightButton;
            break;

        case OIS::MB_Middle:
            return CEGUI::MiddleButton;
            break;

        default:
            return CEGUI::LeftButton;
            break;
    }
}

bool PlaneWorld::mouseMoved( const OIS::MouseEvent &arg )
{


    //if(CEGUI::System::getSingleton().injectMouseMove(arg.state.X.rel, arg.state.Y.rel)) return   true;
    CEGUI::System::getSingleton().injectMousePosition(arg.state.X.abs, arg.state.Y.abs);
    //CEGUI::System::getSingleton().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    if(arg.state.Y.abs < 0.8 * arg.state.height){
        mCameraMan->injectMouseMove(arg);
    }
    return true;
}

bool PlaneWorld::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //if(CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id))) return true;
    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
    mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool PlaneWorld::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
    //if(CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id))) return true;
    mCameraMan->injectMouseUp(arg, id);
    return true;
}

bool PlaneWorld::quit(const CEGUI::EventArgs &e){
    mShutDown = true;
    return true;
}

bool PlaneWorld::positionSliderMoved(const CEGUI::EventArgs &e){
#if NORMAL_MODE
    // The slider moved.
    CEGUI::WindowManager * winMgr = CEGUI::WindowManager::getSingletonPtr();
    CEGUI::Slider * slider = static_cast<CEGUI::Slider*>(winMgr->getWindow("PositionSlider"));
    //CEGUI::Window * resultWindow = winMgr->getWindow("StaticText1");

    //std::stringstream resultStr;
    //resultStr << "Moved to: " << slider->getCurrentValue();

    //resultWindow->setText(resultStr);
    std::cout << "slider moved " << slider->getCurrentValue() << std::endl;
    for(int i = 0; i<players.size(); i++){
        players[i]->setTime(300.0 * slider->getCurrentValue());
    }
#endif


    return true;
}
bool PlaneWorld::speedSliderMoved(const CEGUI::EventArgs &e){
#if NORMAL_MODE
    // The slider moved.
    CEGUI::WindowManager * winMgr = CEGUI::WindowManager::getSingletonPtr();
    CEGUI::Slider * slider = static_cast<CEGUI::Slider*>(winMgr->getWindow("SpeedSlider"));
    //CEGUI::Window * resultWindow = winMgr->getWindow("StaticText1");

    //std::stringstream resultStr;
    //resultStr << "Moved to: " << slider->getCurrentValue();

    //resultWindow->setText(resultStr);
    std::cout << "slider moved " << slider->getCurrentValue() << std::endl;
    for(int i = 0; i<players.size(); i++){
        players[i]->setSpeed(slider->getCurrentValue()-20.0);
    }

#endif

    return true;
}
//Adjust mouse clipping area
void PlaneWorld::windowResized(Ogre::RenderWindow* rw) 
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;

#if NORMAL_MODE
    std::cout << "resize" << std::endl;
    CEGUI::WindowManager * winMgr = CEGUI::WindowManager::getSingletonPtr();
    CEGUI::Slider * positionSlider= static_cast<CEGUI::Slider*>(winMgr->getWindow("PositionSlider"));
    CEGUI::Slider * speedSlider = static_cast<CEGUI::Slider*>(winMgr->getWindow("SpeedSlider"));


    positionSlider->setPosition(CEGUI::UVector2(
                CEGUI::UDim(0, 10), 
                CEGUI::UDim(0, 0.95 * height - 30)));
    positionSlider->setSize(CEGUI::UVector2(
                CEGUI::UDim(0, 0.9 * width), 
                CEGUI::UDim(0 , 20)));

    speedSlider->setPosition(CEGUI::UVector2(
                CEGUI::UDim(0, 10), 
                CEGUI::UDim(0, 0.95 * height)));
    speedSlider->setSize(CEGUI::UVector2(
                CEGUI::UDim(0, 0.9 * width), 
                CEGUI::UDim(0 , 20)));
#endif
}




