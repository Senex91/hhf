#ifndef SERVER_H
#define SERVER_H

#include "SDL_net.h"
#include "map"
#include "ClientConnection.h"
#include "NetworkConstants.h"
#include "Command.h"

bool operator<(const IPaddress& l, const IPaddress& r);

class Server : public CommandVisitor {
public:
	Server();
	~Server();
	
	void run();
	
	virtual void accept(GameStateCommand&);
	virtual void accept(MoveCommand&);
	virtual void accept(BlinkCommand&);
	virtual void accept(ThrowCommand&);
	
private:
	GameState state;
	
	void processCommand(IPaddress& sender,Command& command);
	
	char id;

	UDPsocket sd;       /* Socket descriptor */
	UDPpacket *p;       /* Pointer to packet memory */
	bool running;

	std::map<IPaddress, ClientConnection*> connections;

};

#endif