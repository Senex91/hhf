#ifndef CLIENT_CONNECTION
#define CLIENT_CONNECTION

#include "GameState.h"
#include "SDL_net.h"
#include <string>
#include "Command.h"

class ClientConnection {
public:
	ClientConnection(IPaddress,char id,UDPsocket& sd);
	~ClientConnection();
	void sendGameState(const GameState&);
	
	
	
	
private:
	void sendText(const std::string&);
	
	IPaddress address;
	UDPsocket& sd;
	UDPpacket *p;
	char id;
};

#endif