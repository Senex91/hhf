#ifndef CLIENT_CONNECTION
#define CLIENT_CONNECTION

#include "GameState.h"
#include "SDL_net.h"

class ClientConnection {
public:
	ClientConnection(IPaddress);
	~ClientConnection();
	void sendGameState(const GameState&);
	
	
	
	
private:
	IPaddress address;
	UDPsocket sd;
	UDPpacket *p;
};

#endif