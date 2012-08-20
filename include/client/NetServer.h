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
	
	void joinServer(const Address&);
	void quitServer();

	void sendCommand(const Command&);
	void receiveData();

	GameState const& getGameState();
	
	virtual void accept(JoinCommand&);
	virtual void accept(IDCommand&);
	virtual void accept(GameStateCommand&);
	virtual void accept(MoveCommand&);
	virtual void accept(BlinkCommand&);
	virtual void accept(ThrowCommand&);
	virtual void accept(SpectateCommand&);
	virtual void accept(QuitCommand&);
	virtual void accept(PlayCommand&);
	
private:
	bool handshaked;
	int id;
	
	Socket socket;
	Address serverAddress;

	GameState latestState;

};
#endif