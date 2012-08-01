#include "Command.h"
#include <sstream>

using std::stringstream;
using std::string;
using std::size_t;
using std::map;

map<string,Command::CommandMaker> Command::deserializers;

void initializeCommand() {
	Command::registerDeserializer(JOIN_CMD,JoinCommand::deserialize);
	Command::registerDeserializer(ID_CMD,IDCommand::deserialize);
	Command::registerDeserializer(MOVE_CMD,MoveCommand::deserialize);
	Command::registerDeserializer(STATE_CMD,GameStateCommand::deserialize);
	Command::registerDeserializer(BLINK_CMD,BlinkCommand::deserialize);
}

Command::~Command() {
	
}

string Command::write() {
	stringstream s;
	output(s);
	return s.str();
}

Command* Command::deserialize(string str) {
	size_t colonPos = str.find(':');
	if(colonPos == string::npos) {
		return NULL;
	}
	string commandType = str.substr(0,colonPos);
	if(!deserializers.count(commandType)) {
		return NULL;
	}
	return deserializers[commandType](str.substr(colonPos+1));
}

CommandVisitor::~CommandVisitor() {
	
}

JoinCommand::~JoinCommand() {
	
}

IDCommand::~IDCommand() {
	
}

GameStateCommand::~GameStateCommand() {
	
}

MoveCommand::~MoveCommand() {
	
}

Command* MoveCommand::deserialize(string s) {
	stringstream stream(s);
	float moveX, moveY;
	stream >> moveX >> moveY;
	return new MoveCommand(moveX,moveY);
}

BlinkCommand::~BlinkCommand() {
	
}

Command* BlinkCommand::deserialize(string s) {
	stringstream stream(s);
	float moveX, moveY;
	stream >> moveX >> moveY;
	return new BlinkCommand(moveX,moveY);
}