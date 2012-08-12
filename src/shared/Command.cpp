#include "Command.h"
#include <sstream>

using std::stringstream;
using std::string;
using std::size_t;
using std::map;

map<string,Command::CommandMaker> Command::deserializers;

Command::~Command() {
	
}

string Command::write() const {
	stringstream s;
	output(s);
	return s.str();
}

Command* Command::deserialize(string str) {
	static bool joinCmd = registerDeserializer(JOIN_CMD,JoinCommand::deserialize) && joinCmd;
	static bool idCmd = registerDeserializer(ID_CMD,IDCommand::deserialize) && idCmd;
	static bool moveCmd = registerDeserializer(MOVE_CMD,MoveCommand::deserialize) && moveCmd;
	static bool stateCmd = registerDeserializer(STATE_CMD,GameStateCommand::deserialize) && stateCmd;
	static bool blinkCmd = registerDeserializer(BLINK_CMD,BlinkCommand::deserialize) && blinkCmd;
	static bool throwCmd = registerDeserializer(THROW_CMD,ThrowCommand::deserialize) && throwCmd;
	static bool spectateCmd = registerDeserializer(SPECTATE_CMD,SpectateCommand::deserialize) && spectateCmd;
	static bool quitCmd = registerDeserializer(QUIT_CMD,QuitCommand::deserialize) && quitCmd;
	
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

SpectateCommand::~SpectateCommand() {
	
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

ThrowCommand::~ThrowCommand() {
	
}

Command* ThrowCommand::deserialize(string s) {
	stringstream stream(s);
	int id;
	stream >> id;
	return new ThrowCommand(id);
}

QuitCommand::~QuitCommand() {
	
}