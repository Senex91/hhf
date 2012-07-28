#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <string>//
#include <shared/GameState.h>
#include <SDL_net.h>

class ServerConnection {
public:
    ServerConnection(std::string, int);
    ~ServerConnection();

    GameState getGameState();

private:
    UDPsocket socket;
    UDPpacket* packet;


};

#endif

    


