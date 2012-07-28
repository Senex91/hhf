#ifndef SERVER_H
#define SERVER_H

#include "SDL_net.h"
#include "map"
#include "ClientConnection.h"
#include "NetworkConstants.h"

bool operator<(const IPaddress& l, const IPaddress& r);

class Server {
public:
	Server();
	~Server();
	
	void run();
	
private:

	UDPsocket sd;       /* Socket descriptor */
	UDPpacket *p;       /* Pointer to packet memory */
	bool running;

	std::map<IPaddress, ClientConnection*> connections;

};

#endif