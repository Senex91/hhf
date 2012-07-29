#ifndef COMMAND_H
#define COMMAND_H

#include "GameState.h"
#include "NetworkConstants.h"
#include "Util.h"

class Command;
class GameStateCommand;
class MoveCommand;
class BlinkCommand;
class ThrowCommand;
class CommandVisitor;

Command* deserializeCommand();

class Command {
public:
	Command() {}
	virtual ~Command();
	
	virtual std::string write() = 0;
	virtual void visit(CommandVisitor& cv) = 0;
	
private:
	
};

class CommandVisitor {
public:
	CommandVisitor() {}
	virtual ~CommandVisitor();
	
	virtual void accept(GameStateCommand&) {}
	virtual void accept(MoveCommand&) {}
	virtual void accept(BlinkCommand&) {}
	virtual void accept(ThrowCommand&) {}
	
private:
	
};

class GameStateCommand : public Command {
public:
	GameStateCommand(const GameState& g) : gameState(g) {}
	virtual ~GameStateCommand();
	
	inline const GameState& getGameState() { return gameState; }
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	virtual std::string write() { return std::string(1,STATE_CMD) + serializeGameState(gameState); }
	
private:
	GameState gameState;
};

class MoveCommand : public Command {
public:
	MoveCommand(char player,float moveX,float moveY) : player(player), moveX(moveX), moveY(moveY) {}
	virtual ~MoveCommand();
	
	inline const char& getPlayer() { return player; }
	inline const float& getMoveX() { return moveX; }
	inline const float& getMoveY() { return moveY; }
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	virtual std::string write();
	
private:
	char player;
	float moveX, moveY;
};

class BlinkCommand : public Command {
public:
	BlinkCommand(char player,float moveX,float moveY) : player(player), moveX(moveX), moveY(moveY) {}
	virtual ~BlinkCommand();
	
	inline const char& getPlayer() { return player; }
	inline const float& getMoveX() { return moveX; }
	inline const float& getMoveY() { return moveY; }
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	virtual std::string write();
	
private:
	char player;
	float moveX, moveY;
};

#endif