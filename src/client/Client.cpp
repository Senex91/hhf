#include "Client.h"

#include <cstddef>

Client* Client::instance = NULL;

Client* Client::getInstance(){
	if(!instance){
		instance = new Client;
	}
	return instance;
}

Client::Client(){
	
}