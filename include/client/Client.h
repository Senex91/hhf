#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "GameRenderer.h"
#include "NetServer.h"

/**
 * @brief Client runs a Client instance of a game.
 * The Client is a singleton that enables all subcomponents 
 * to access each other.
 */
class Client {
public:
	static Client& getInstance();

	void run();

private:

	// Singleton things
	Client();
	~Client();
	Client (Client const&);
	Client& operator=(Client const&);
	// static Client* instance;

	// data
	GameRenderer gameRenderer;
	bool running;

};

#endif
