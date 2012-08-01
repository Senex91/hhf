#ifndef CLIENT_CONNECTION
#define CLIENT_CONNECTION

#include "GameState.h"
#include "UDPConnection.h"
#include <string>
#include "Command.h"

class ClientConnection : public CommandVisitor {
public:
	ClientConnection(Address,int id,Socket& sd);
	~ClientConnection();
	void sendGameState(const GameState&);
	
	void processCommand(Command*);
	
	virtual void accept(JoinCommand&);
	virtual void accept(IDCommand&);
	virtual void accept(GameStateCommand&);
	virtual void accept(MoveCommand&);
	virtual void accept(BlinkCommand&);
	
private:
	void sendText(const std::string&);
	
	Address address;
	Socket& socket;
	int id;
};

#endif