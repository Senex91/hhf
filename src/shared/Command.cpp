#include "Command.h"
#include <sstream>

using std::stringstream;
using std::string;

Command::~Command() {
	
}

CommandVisitor::~CommandVisitor() {
	
}

GameStateCommand::~GameStateCommand() {
	
}

MoveCommand::~MoveCommand() {
	
}

std::string MoveCommand::write() {
	stringstream s;
	s << player;
	s << moveX << " ";
	s << moveY << " ";
	return s.str();
}

BlinkCommand::~BlinkCommand() {
	
}

std::string BlinkCommand::write() {
	stringstream s;
	s << player;
	s << moveX << " ";
	s << moveY << " ";
	return s.str();
}

Command* deserializeCommand(std::string command) {
	char which = command[0];
	switch(which) {
		case STATE_CMD:
			return new GameStateCommand(deserializeGameState(command.substr(1)));
			break;
		case MOVE_CMD: {
			char player = command[1];
			stringstream rest(command.substr(2));
			float moveX,moveY;
			rest >> moveX; rest >> moveY;
			return new MoveCommand(player,moveX,moveY);
		} break;
		case BLINK_CMD: {
			char player = command[1];
			stringstream rest(command.substr(2));
			float moveX,moveY;
			rest >> moveX; rest >> moveY;
			return new BlinkCommand(player,moveX,moveY);
		} break;
	}
	return NULL;
}