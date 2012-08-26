// GamePhysicsTestSuite.h
#include <cxxtest/TestSuite.h>
#include "GamePhysics.h"
#include "Debug.h"


class GamePhysicsTestSuite : public CxxTest::TestSuite {

	GamePhysics* physics;
public:

    void setUp(){
    	physics = new GamePhysics();
        // _buffer = new char[1024];
    }

	void testAddPlayer(void) {

		for(int i = 0; i<1000; i++){
			physics->tick();
			TS_ASSERT(physics->getGameState().elves.size() == 0);
			TS_ASSERT(physics->getGameState().orb.id == -1);
		}

		physics->addPlayer(1);

		for(int i = 0; i<1000; i++){
			physics->tick();
			TS_ASSERT(physics->getGameState().elves.size() == 1);
			TS_ASSERT(physics->getGameState().orb.id == 1);
		}

		physics->removePlayer(1);

		for(int i = 0; i<1000; i++){
			physics->tick();
			TS_ASSERT(physics->getGameState().elves.size() == 0);
			TS_ASSERT(physics->getGameState().orb.id == -1);
		}
	}

	void testPlayerSetGoal(void){

		// int PLAYER_ID = 0;
		double goalX = 2;
		double goalY = 2;

		int numPlayers = 0;

		for(int PLAYER_ID = 0; PLAYER_ID< 10; PLAYER_ID++){

			// INITIAL STATE
			for(int i = 0; i<1000; i++){
				physics->tick();
				TS_ASSERT(physics->getGameState().elves.size() == numPlayers);
				// TS_ASSERT(physics->getGameState().orb.id == -1);
				// TS_ASSERT(physics->getGameState().orb.x == 0);
				// TS_ASSERT(physics->getGameState().orb.y == 0);
			}

			//ADDED PLAYER
			physics->addPlayer(PLAYER_ID);
			numPlayers++;
			for(int i = 0; i<1000; i++){
				physics->tick();
				TS_ASSERT(physics->getGameState().elves.size() == numPlayers);
				// TS_ASSERT(physics->getGameState().orb.id == PLAYER_ID);
				//orb starts at player position
				// TS_ASSERT(physics->getGameState().orb.x 
				// 	== physics->getGameState().elves[PLAYER_ID].x);
				// TS_ASSERT(physics->getGameState().orb.y 
				// 	== physics->getGameState().elves[PLAYER_ID].y);
			}

			//PLAYER MOVE
			physics->playerSetGoal(PLAYER_ID, goalX, goalY);
			for(int i = 0; i<100000; i++){
				physics->tick();
				// TS_ASSERT(physics->getGameState().orb.x 
				// 	== physics->getGameState().elves[PLAYER_ID].x);
				// TS_ASSERT(physics->getGameState().orb.y 
				// 	== physics->getGameState().elves[PLAYER_ID].y);

				// TS_ASSERT(physics->getGameState().orb.x 
				// 	!= physics->getGameState().elves[1].x);
				// TS_ASSERT(physics->getGameState().orb.y 
				// 	!= physics->getGameState().elves[1].y);
			}

			TS_ASSERT(physics->getGameState().elves[PLAYER_ID].x == goalX);
			TS_ASSERT(physics->getGameState().elves[PLAYER_ID].y == goalY);

			DEBUG(gameStateToString(physics->getGameState()));
		}

		





	}

	// void goalTest()


};