// GamePhysicsTestSuite.h
#include <cxxtest/TestSuite.h>
#include "GamePhysics.h"

class GamePhysicsTestSuite : public CxxTest::TestSuite {

	GamePhysics* physics;
public:

    void setUp(){
    	physics = new GamePhysics();
        // _buffer = new char[1024];
    }

	void testAddPlayer(void) {
		TS_ASSERT(physics->getGameState().elves.size() == 0);
		physics->addPlayer(1);
		TS_ASSERT(physics->getGameState().elves.size() == 1);
		physics->addPlayer(0);
		TS_ASSERT(physics->getGameState().elves.size() == 2);
	}

	// void 

};