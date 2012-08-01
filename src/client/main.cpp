
#include "Client.h"
#include "Debug.h"

#include <string>

int main(){
    // Create application object
    //PlaneWorld app;
    //ITutorial01 app;
    //ITutorial02 app;
    //BasicTutorial7 app;
    //DemoSample demo;

    //return demo.run();
    
    DEBUG("starting client");

    // std::vector<Elf> elves;
    // elves.push_back((Elf) {1, 0, 0, 0, 0});
    // elves.push_back((Elf) {2, 0, 1, 0, 0});
    // elves.push_back((Elf) {3, 1, 0, 0, 0});
    // GameState state1;
    // state1.elves = elves;
    // state1.felhound = (Felhound) {2,2, 0, 0};


    // GameState state2;
    // state2 = state1;

    // DEBUG(gameStateToString(state2));

    Client& client = Client::getInstance();
    // DEBUG("RUNNING CLIENT...............................");
    client.initialize();
    client.run();
    // client.name = "Andrew";

    // DEBUG(client.name);
    // DEBUG((Client::getInstance()).name);
    
    // Game game;

    // try {
    //     game.run();
    // } catch( Ogre::Exception& e ) {
    //     std::cerr << "An exception has occured: " <<
    //         e.getFullDescription().c_str() << std::endl;
    // }



    return 0;
}



