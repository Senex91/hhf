#include "GameState.h"
#include <sstream>
#include <iostream>

using std::stringstream;
using std::vector;
using std::string;

GameState::GameState(void):elves(){

}

GameState::GameState(const GameState& other):elves(other.elves){
	felhound = other.felhound;
}

const GameState& GameState::operator=(const GameState& other){
	elves = other.elves;
	//elves.clear();
	// for(int i = 0; i<other.elves.size(); i++){
	// 	elves.push_back(other.elves[i]);
	// }
	felhound = other.felhound;
	return *this;
}

std::string serializeGameState(const GameState& gs) {
	static string delim = " ";
	stringstream ret;
	ret << gs.felhound.x << delim;
	ret << gs.felhound.y << delim;
	ret << gs.felhound.xvel << delim;
	ret << gs.felhound.yvel << delim;
	ret << gs.elves.size() << delim;
	for(unsigned int i=0;i<gs.elves.size();i++) {
		ret << gs.elves[i].x << delim;
		ret << gs.elves[i].y << delim;
		ret << gs.elves[i].xvel << delim;
		ret << gs.elves[i].yvel << delim;
		ret << gs.elves[i].xgoal << delim;
		ret << gs.elves[i].ygoal << delim;
		ret << gs.elves[i].id << delim;
	}
	
	return ret.str();
}


std::string gameStateToString(const GameState& gs) {
	stringstream ret;
	ret << "{GameState:\n";
	ret << "{FH: pos=";
	ret << "(" << gs.felhound.x << "," << gs.felhound.y << "), vel=(" << gs.felhound.xvel << "," << gs.felhound.yvel << ")}\n";
	ret << gs.elves.size() << "Elves:\n";
	for(unsigned int i=0;i<gs.elves.size();i++) {
		ret << "[";
		ret << "id=" << gs.elves[i].id << ", ";
		ret << "pos=(" << gs.elves[i].x << ", " << gs.elves[i].y << "), ";
		ret << "vel=(" << gs.elves[i].xvel << ", " << gs.elves[i].yvel << ")";
		ret << "goal=(" << gs.elves[i].xgoal << ", " << gs.elves[i].ygoal << ")";
		ret << "]\n";
	}
	ret << "}";
	
	return ret.str();
}
GameState deserializeGameState(const std::string& str) {
	GameState ret;
	stringstream read(str);
	read >> ret.felhound.x;
	read >> ret.felhound.y;
	read >> ret.felhound.xvel;
	read >> ret.felhound.yvel;
	int n; read >> n;
	
	for(int i=0;i<n;i++) {
		Elf e;
		read >> e.x;
		read >> e.y;
		read >> e.xvel;
		read >> e.yvel;
		read >> e.xgoal;
		read >> e.ygoal;
		read >> e.id;
		ret.elves.push_back(e);
	}
	
	return ret;
}