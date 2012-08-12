#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include "UDPConnection.h"
#include "map"
#include "NetClient.h"
#include "NetworkConstants.h"
#include "Command.h"

class NetManager {
public:
	NetManager();
	~NetManager();
	
	void update();
	
	NetClient* getClient(int id);
	void removeClient(int id);
	
private:
	GameState state;
	
	int id;
	int timer;
	
	bool running;
	
	Socket socket;
	
	std::map<Address, NetClient*> connections;
	
};

#endif