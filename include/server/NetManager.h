#ifndef SERVER_H
#define SERVER_H

#include "UDPConnection.h"
#include "map"
#include "NetClient.h"
#include "NetworkConstants.h"
#include "Command.h"

class NetManager {
public:
	NetManager();
	~NetManager();
	
	void run();
	
private:
	GameState state;
	
	int id;
	
	bool running;
	
	Socket socket;
	
	std::map<Address, NetClient*> connections;
	
};

#endif