#ifndef SERVER_H
#define SERVER_H

#include "UDPConnection.h"
#include "map"
#include "ClientConnection.h"
#include "NetworkConstants.h"
#include "Command.h"

class Server {
public:
	Server();
	~Server();
	
	void run();
	
private:
	GameState state;
	
	int id;
	
	bool running;
	
	Socket socket;
	
	std::map<Address, ClientConnection*> connections;
	
};

#endif