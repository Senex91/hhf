#ifndef NETSERVER_H
#define NETSERVER_H

#include "GameState.h"
/**
 * @brief A netserver provides the network interface to the server, which  
 * involves sending it commands and for us to access the latest gamestate.
 */
class NetServer {
public:
	NetServer();
	~NetServer();

	void sendCommand();

	GameState const& getGameState();
	
private:

	GameState latestState;

};
#endif