#ifndef COMMAND_H
#define COMMAND_H

#include "GameState.h"
#include "NetworkConstants.h"
#include "Util.h"
#include <sstream>
#include <map>

class Command;
class GameStateCommand;
class JoinCommand;
class SpectateCommand;
class IDCommand;
class MoveCommand;
class BlinkCommand;
class CommandVisitor;
class ThrowCommand;
class QuitCommand;

class Command {
private:
	typedef Command* (*CommandMaker)(std::string);
public:
	Command() {}
	virtual ~Command();
	
	virtual std::string write() const;
	virtual void visit(CommandVisitor& cv) = 0;
	
	static bool registerDeserializer(std::string s, CommandMaker m) { deserializers[s] = m; return true; }
	static Command* deserialize(std::string str);
	
protected:
	virtual void output(std::stringstream& s) const = 0;
private:
	static std::map<std::string,CommandMaker> deserializers;
};

class CommandVisitor {
public:
	CommandVisitor() {}
	virtual ~CommandVisitor();
	
	virtual void accept(JoinCommand&) {}
	virtual void accept(IDCommand&) {}
	virtual void accept(GameStateCommand&) {}
	virtual void accept(MoveCommand&) {}
	virtual void accept(BlinkCommand&) {}
	virtual void accept(ThrowCommand&) {}
	virtual void accept(SpectateCommand&) {}
	virtual void accept(QuitCommand&) {}
	
private:
	
};

class JoinCommand : public Command {
public:
	JoinCommand() {}
	virtual ~JoinCommand();
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	
	static Command* deserialize(std::string) { return new JoinCommand(); }
	
protected:
	
	virtual void output(std::stringstream& s) const { s << JOIN_CMD << ":"; }
	
};

class SpectateCommand : public Command {
public:
	SpectateCommand() {}
	virtual ~SpectateCommand ();
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	
	static Command* deserialize(std::string) { return new SpectateCommand(); }
	
protected:
	
	virtual void output(std::stringstream& s) const { s << SPECTATE_CMD << ":"; }
	
};

class IDCommand : public Command {
public:
	IDCommand(int id) : id(id) {}
	virtual ~IDCommand();
	
	const int& getID() const { return id; }
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	
	static Command* deserialize(std::string s) { std::stringstream stream(s); int id; stream >> id; return new IDCommand(id); }
	
protected:
	
	int id;
	
	virtual void output(std::stringstream& s) const { s << ID_CMD << ":" << id; }
};

class GameStateCommand : public Command {
public:
	GameStateCommand(const GameState& g) : gameState(g) {}
	virtual ~GameStateCommand();
	
	inline const GameState& getGameState() const { return gameState; }
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	
	static Command* deserialize(std::string str) { return new GameStateCommand(deserializeGameState(str)); }
	
protected:
	
	virtual void output(std::stringstream& s) const { s << STATE_CMD << ":" << serializeGameState(gameState); }
	
private:
	GameState gameState;
};

class MoveCommand : public Command {
public:
	MoveCommand(float moveX,float moveY) : moveX(moveX), moveY(moveY) {}
	virtual ~MoveCommand();
	
	// inline const char& getPlayer() { return player; }
	inline const float& getMoveX() const { return moveX; }
	inline const float& getMoveY() const { return moveY; }
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	
	static Command* deserialize(std::string str);
	
protected:
	
	virtual void output(std::stringstream& s) const { s << MOVE_CMD << ":" << moveX << " " << moveY; }
	
private:
	// char player;
	float moveX, moveY;
};

class BlinkCommand : public Command {
public:
	BlinkCommand(float moveX,float moveY) : moveX(moveX), moveY(moveY) {}
	virtual ~BlinkCommand();
	
	inline const float& getMoveX() const { return moveX; }
	inline const float& getMoveY() const { return moveY; }
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	
	static Command* deserialize(std::string str);
	
protected:
	
	virtual void output(std::stringstream& s) const { s << BLINK_CMD << ":" << moveX << " " << moveY; }
	
private:
	float moveX, moveY;
};

class ThrowCommand : public Command {
public:
	ThrowCommand(const int& id) : id(id) {}
	virtual ~ThrowCommand();
	
	inline const int& getID() const { return id; }
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	
	static Command* deserialize(std::string str);
	
protected:
	
	virtual void output(std::stringstream& s) const { s << THROW_CMD << ":" << id; }
	
private:
	int id;
};

class QuitCommand : public Command {
public:
	QuitCommand() {}
	virtual ~QuitCommand();
	
	virtual void visit(CommandVisitor& cv) { cv.accept(*this); }
	
	static Command* deserialize(std::string str) { return new QuitCommand(); }
	
protected:
	virtual void output(std::stringstream& s) const { s << QUIT_CMD << ":"; }
};

#endif