#ifndef NETSERVER_H
#define NETSERVER_H

#include "GameState.h"
#include "Command.h"
#include "UDPConnection.h"
/**
 * @brief A netserver provides the network interface to the server, which  
 * involves sending it commands and for us to access the latest gamestate.
 */
class NetServer : public CommandVisitor {
public:
	NetServer();
	~NetServer();

	void sendCommand();
	void receiveData();

	GameState const& getGameState();
	
	virtual void accept(JoinCommand&);
	virtual void accept(IDCommand&);
	virtual void accept(GameStateCommand&);
	virtual void accept(MoveCommand&);
	virtual void accept(BlinkCommand&);
	
private:
	bool handshaked;
	int id;
	
	Socket socket;
	Address serverAddress;

	GameState latestState;

};
#endif