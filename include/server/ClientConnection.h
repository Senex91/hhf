#ifndef CLIENT_CONNECTION
#define CLIENT_CONNECTION

#include "SDL_net.h"

class ClientConnection {
public:
	ClientConnection(IPaddress);
	~ClientConnection();
	
	
	
	
private:
	IPaddress address;
	UDPsocket sd;
	UDPpacket *p;
};

#endif