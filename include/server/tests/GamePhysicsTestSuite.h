// GamePhysicsTestSuite.h
#include <cxxtest/TestSuite.h>
#include "GamePhysics.h"
#include "Debug.h"

#define NUM_PLAYERS 20

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

		unsigned int numPlayers = 0;
		for(int PLAYER_ID = 0; PLAYER_ID < NUM_PLAYERS; PLAYER_ID++){

			double goalX = PLAYER_ID;
			double goalY = PLAYER_ID;


			// INITIAL STATE
			for(unsigned int i = 0; i<1000; i++){
				physics->tick();
				TS_ASSERT(physics->getGameState().elves.size() == numPlayers);
				// TS_ASSERT(physics->getGameState().orb.id == -1);
				// TS_ASSERT(physics->getGameState().orb.x == 0);
				// TS_ASSERT(physics->getGameState().orb.y == 0);
			}

			//ADDED PLAYER
			physics->addPlayer(PLAYER_ID);
			numPlayers++;
			for(unsigned int i = 0; i<1000; i++){
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
			for(unsigned int i = 0; i<100000; i++){
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

			// DEBUG(gameStateToString(physics->getGameState()));
		}
	}

	void testPlayerThrow(void){

		/******** INITIAL GAME STATE *******/
		for(unsigned int i = 0; i<1000; i++){
			physics->tick();
			TS_ASSERT(physics->getGameState().elves.size() == 0);
			TS_ASSERT(physics->getGameState().orb.id == -1);
			TS_ASSERT(physics->getGameState().orb.x == 0);
			TS_ASSERT(physics->getGameState().orb.y == 0);
		}


		/******** PLAYERS LINED UP *******/
		unsigned int numPlayers = 0;
		for(unsigned int PLAYER_ID = 0; PLAYER_ID< NUM_PLAYERS; PLAYER_ID++){

			double goalX = PLAYER_ID;
			double goalY = PLAYER_ID;


			// INITIAL STATE
			for(unsigned int i = 0; i<1000; i++){
				physics->tick();
				TS_ASSERT(physics->getGameState().elves.size() == numPlayers);
			}

			//ADDED PLAYER
			physics->addPlayer(PLAYER_ID);
			numPlayers++;
			for(unsigned int i = 0; i<1000; i++){
				physics->tick();
				TS_ASSERT(physics->getGameState().elves.size() == numPlayers);
			}

			//PLAYER MOVE
			physics->playerSetGoal(PLAYER_ID, goalX, goalY);
			for(unsigned int i = 0; i<100000; i++){
				physics->tick();
			}

			TS_ASSERT(physics->getGameState().elves[PLAYER_ID].x == goalX);
			TS_ASSERT(physics->getGameState().elves[PLAYER_ID].y == goalY);
		}




		/******** THROW BALL *******/
		// int currentOrbOwner = physics->getGameState().orb.id;

		for(int throwerID = 1; throwerID < NUM_PLAYERS; throwerID++){
			for(int targetID = throwerID + 1; targetID < NUM_PLAYERS; targetID++){

				//Throw from previous owner to current thrower
				int currentOrbOwner = physics->getGameState().orb.id;
				physics->playerThrow(currentOrbOwner, throwerID);
				for(unsigned int i = 0; i<1000; i++){
					physics->tick();
				}
				TS_ASSERT(physics->getGameState().orb.id == throwerID);
				TS_ASSERT(physics->getGameState().orb.x 
					== physics->getGameState().elves[throwerID].x);
				TS_ASSERT(physics->getGameState().orb.y
					== physics->getGameState().elves[throwerID].y);


				//Throw to target
				physics->playerThrow(throwerID, targetID);
				for(unsigned int i = 0; i<1000; i++){
					physics->tick();
				}
				TS_ASSERT(physics->getGameState().orb.id == targetID);
				TS_ASSERT(physics->getGameState().orb.x 
					== physics->getGameState().elves[targetID].x);
				TS_ASSERT(physics->getGameState().orb.y
					== physics->getGameState().elves[targetID].y);


				//Throw back to thrower
				physics->playerThrow(targetID, throwerID);
				for(unsigned int i = 0; i<1000; i++){
					physics->tick();
				}
				TS_ASSERT(physics->getGameState().orb.id == throwerID);
				TS_ASSERT(physics->getGameState().orb.x 
					== physics->getGameState().elves[throwerID].x);
				TS_ASSERT(physics->getGameState().orb.y
					== physics->getGameState().elves[throwerID].y);




			}
		}



	}

	// void checkThrowState(int )


};