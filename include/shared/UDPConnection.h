#ifndef UDP_CONNECTION_H
#define UDP_CONNECTION_H

/**
 * Important: Everything here assumes SDL_Init and SDLNet_Init were already called and were successful.
 */

#include <SDL.h>
#include <SDL_net.h>
#include <string>
#include <vector>

class Address {
public:
	Address(Uint32 host,Uint16 port);
	Address(const std::string& host,Uint16 port);
	Address(const IPaddress&);
	Address(const Address&);
	~Address();
	const Address& operator=(const Address&);
	
	bool operator<(const Address&) const; //so this can be used in std::map
	
	std::string getHostName();
	Uint32 getHostNum() const;
	Uint16 getPort() const;
	const IPaddress& getWrapped() const;
	
	void setHostName(const std::string&);
	void setPort(Uint16);
	void setHostNum(Uint32);
	void setWrapped(const IPaddress&);
	
private:
	IPaddress wrapped;
};

class Packet {
public:
	Packet();
	Packet(UDPpacket*); //assumes ownership
	Packet(const Packet&);
	Packet(const std::string& data);
	Packet(const char* data,unsigned int length);
	~Packet();
	const Packet& operator=(const Packet& other);
	
	bool isValid() const;
	
	int getChannel() const;
	std::string getData() const;
	int getLength() const;
	int getMaxLength() const;
	Address getAddress() const;
	//Use with care. May return NULL.
	const char* getDataRaw() const;
	const UDPpacket* getWrapped() const;
	
	void setChannel(int);
	void setData(const std::string&);
	void setAddress(const Address&);
	void setAddress(const IPaddress&);
	//Use with care.
	void setDataRaw(const char*,unsigned int length);
	void setWrapped(UDPpacket*); //assumes ownership
	
	static const unsigned int MAX_LENGTH;
private:
	void setBlank();
	void deleteWrapped();
	
	UDPpacket* wrapped;
	
	static std::vector<UDPpacket*> unusedPacketStack;
	static UDPpacket* acquireUDPpacket();
	static void freeUDPpacket(UDPpacket* packet);
	
	friend class Socket;
};

/*
class Command {
public:
	Command();
	virtual ~Command();
	
	virtual std::string get
};*/

class Socket {
public:
	Socket();
	Socket(Uint16 port);
	Socket(UDPsocket);
	~Socket();
	
	bool isValid() const;
	
	Packet getPacket();
	bool sendPacket(Packet&);
	
private:
	UDPsocket wrapped;
	
	Socket(const Socket&) {}
	const Socket& operator=(const Socket&);
};

#endif