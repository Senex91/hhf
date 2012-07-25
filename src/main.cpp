
#include "PlaneWorld.h"

int main(){
    // Create application object
    PlaneWorld app;
    //ITutorial01 app;
    //ITutorial02 app;
    //BasicTutorial7 app;
    //DemoSample demo;

    //return demo.run();

    try {
        app.go();
    } catch( Ogre::Exception& e ) {
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
    }



    return 0;
}



