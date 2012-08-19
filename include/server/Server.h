#ifndef SERVER_H
#define SERVER_H

#include "NetManager.h"
#include "GamePhysics.h"
#include "TimerManager.h"

class Server {
public:
	static Server& getInstance();
	~Server();
	
	void run();
	
	void setRunning(const bool& b) { running = b; }
	
	NetManager& getNetManager() { return net; }
	GamePhysics& getGamePhysics() { return phys; }
	TimerManager& getTimerManager() { return tm; }
	
private:
	bool running;
	NetManager net;
	GamePhysics phys;
	TimerManager tm;
	
	Server();
	Server(const Server&) {}
	const Server& operator=(const Server&) { return *this; }
};
#endif