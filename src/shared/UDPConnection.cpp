#include "UDPConnection.h"
#include <string.h>

using std::string;

Address::Address(Uint32 host,Uint16 port) {
	setHostNum(host);
	setPort(port);
}

Address::Address(const string& host,Uint16 port) {
	setPort(port);
	setHostName(host);
}

Address::Address(const IPaddress& other) {
	wrapped = other;
}

Address::Address(const Address& other) {
	wrapped = other.wrapped;
}

Address::~Address() {
	
}

const Address& Address::operator=(const Address& other) {
	wrapped = other.wrapped;
	return *this;
}

bool Address::operator<(const Address& other) const {
	if(wrapped.host == other.wrapped.host) {
		return wrapped.port < other.wrapped.port;
	}
	return wrapped.host < other.wrapped.host;
}

string Address::getHostName() {
	return string(SDLNet_ResolveIP(&wrapped));
}

Uint32 Address::getHostNum() const {
	return wrapped.host;
}

Uint16 Address::getPort() const {
	return wrapped.port;
}

const IPaddress& Address::getWrapped() const {
	return wrapped;
}

void Address::setHostName(const string& s) {
	SDLNet_ResolveHost(&wrapped,s.c_str(),wrapped.port);
}

void Address::setPort(Uint16 port) {
	wrapped.port = port;
}

void Address::setHostNum(Uint32 host) {
	wrapped.host = host;
}

void Address::setWrapped(const IPaddress& newWrapped) {
	wrapped = newWrapped;
}

//--------------------------------------//

const unsigned int Packet::MAX_LENGTH = 512;

Packet::Packet() : wrapped(0) {
	setBlank();
}

Packet::Packet(UDPpacket* toWrap) : wrapped(toWrap) {
	
}

Packet::Packet(const string& data) : wrapped(0) {
	setBlank();
	setData(data);
}

Packet::Packet(const char* data,unsigned int length) : wrapped(0) {
	setBlank();
	setDataRaw(data,length);
}

Packet::Packet(const Packet& other) : wrapped(0) {
	setWrapped(other.wrapped);
}

Packet::~Packet() {
	deleteWrapped();
}

const Packet& Packet::operator=(const Packet& other) {
	deleteWrapped();
	setWrapped(other.wrapped);
	return *this;
}

void Packet::setBlank() {
	deleteWrapped();
	wrapped = SDLNet_AllocPacket(MAX_LENGTH);
	if(wrapped) {
		wrapped->maxlen = MAX_LENGTH;
		wrapped->channel = -1;
		wrapped->len = 0;
		wrapped->data[0] = 0;
		wrapped->address.host = 0;
		wrapped->address.port = 0;
	}
}

bool Packet::isValid() const {
	return wrapped != 0;
}

void Packet::setWrapped(UDPpacket* other) {
	deleteWrapped();
	if(other) {
		wrapped = SDLNet_AllocPacket(other->maxlen);
		if(wrapped) {
			wrapped->channel = other->channel;
			//We can strncpy immediately to our wrapped->data, as it is allocated by SDLNet_AllocPacket
			strncpy((char*)wrapped->data,(char*)other->data,other->len);
			wrapped->len = other->len;
			wrapped->maxlen = other->maxlen;
			wrapped->address.host = other->address.host;
			wrapped->address.port = other->address.port;
		}
	}
}

void Packet::deleteWrapped() {
	if(wrapped) {
		SDLNet_FreePacket(wrapped);
		wrapped = NULL;
	}
}

int Packet::getChannel() const {
	return wrapped ? wrapped->channel : 0;
}

string Packet::getData() const {
	return wrapped ? string((char*)wrapped->data,wrapped->len) : string();
}

int Packet::getLength() const {
	return wrapped ? wrapped->len : 0;
}

int Packet::getMaxLength() const {
	return wrapped ? wrapped->maxlen : 0;
}

Address Packet::getAddress() const {
	return wrapped ? Address(wrapped->address) : Address(0,0);
}

const char* Packet::getDataRaw() const {
	return wrapped ? (const char*)wrapped->data : NULL;
}

const UDPpacket* Packet::getWrapped() const {
	return wrapped;
}

void Packet::setChannel(int i) {
	if(wrapped) {
		wrapped->channel = i;
	}
}

void Packet::setAddress(const Address& address) {
	if(wrapped) {
		wrapped->address = address.getWrapped();
	}
}

void Packet::setData(const string& s) {
	//Because && short-circuits, wrapped->maxlen isn't used when wrapped is NULL.
	if(wrapped && s.length()+1 < (unsigned int)wrapped->maxlen) {
		strncpy((char*)wrapped->data,s.c_str(),s.length()+1);
		wrapped->len = s.length()+1;
	}
}

void Packet::setDataRaw(const char* data,unsigned int length) {
	//Because && short-circuits, wrapped->maxlen isn't used when wrapped is NULL.
	if(wrapped && data && length <= (unsigned int)wrapped->maxlen) {
		strncpy((char*)wrapped->data,data,length);
		wrapped->len = length;
	}
}

//---------------------//

Socket::Socket() {
	wrapped = SDLNet_UDP_Open(0);
}

Socket::Socket(Uint16 port) {
	wrapped = SDLNet_UDP_Open(port);
}

Socket::~Socket() {
	if(wrapped) {
		SDLNet_UDP_Close(wrapped);
	}
}

bool Socket::isValid() const {
	return wrapped != 0;
}

Packet Socket::getPacket() {
	if(wrapped) {
		Packet ret;
		if(SDLNet_UDP_Recv(wrapped,ret.wrapped)) {
			return ret;
		}
	}
	return Packet(NULL);
}

bool Socket::sendPacket(Packet& packet) {
	if(wrapped && packet.isValid()) {
		SDLNet_UDP_Send(wrapped,packet.wrapped->channel,packet.wrapped);
	}
	return false;
}











