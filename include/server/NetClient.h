#ifndef NET_CLIENT_H
#define NET_CLIENT_H

#include "GameState.h"
#include "UDPConnection.h"
#include <string>
#include "Command.h"

class NetClient : public CommandVisitor {
public:
	NetClient(Address,int id,Socket& sd);
	~NetClient();
	void sendGameState(const GameState&);
	
	void processCommand(Command*);
	
	virtual void accept(JoinCommand&);
	virtual void accept(IDCommand&);
	virtual void accept(GameStateCommand&);
	virtual void accept(MoveCommand&);
	virtual void accept(BlinkCommand&);
	virtual void accept(ThrowCommand&);
	
	inline const int& getID() const { return id; }
	inline const Address& getAddress() const { return address; }
	
private:
	void sendText(const std::string&);
	
	Address address;
	Socket& socket;
	int id;
};

#endif