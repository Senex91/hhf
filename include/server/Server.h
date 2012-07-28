#ifndef SERVER_H
#define SERVER_H
#include "SDL_net.h"

class Server {
public:
	Server();
	~Server();
	
	void run();
	
private:
	UDPsocket sd;       /* Socket descriptor */
	UDPpacket *p;       /* Pointer to packet memory */
	bool running;
};

#endif