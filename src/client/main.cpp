
//#include "PlaneWorld.h"
#include "Game.h"
#include "Debug.h"

int main(){
    // Create application object
    //PlaneWorld app;
    //ITutorial01 app;
    //ITutorial02 app;
    //BasicTutorial7 app;
    //DemoSample demo;

    //return demo.run();
    
    DEBUG("starting client");
    
    Game game;

    try {
        game.run();
    } catch( Ogre::Exception& e ) {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }



    return 0;
}



