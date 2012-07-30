#ifndef CLIENT_H
#define CLIENT_H

#include <string>

/**
 * @brief Client runs a Client instance of a game.
 * The Client is a singleton that enables all subcomponents 
 * to access each other.
 */
class Client {
public:
	static Client* getInstance();

	std::string name;
	
private:

	// Singleton things
	Client();
	Client (Client const&);
	Client& operator=(Client const&);
	static Client* instance;

	// data

};

#endif
