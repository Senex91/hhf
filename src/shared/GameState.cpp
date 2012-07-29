#include "GameState.h"
#include <sstream>
#include <iostream>

using std::stringstream;
using std::vector;
using std::string;

std::string serializeGameState(const GameState& gs) {
	stringstream ret;
	string delim = " ";
	ret << gs.felhound.x << delim;
	ret << gs.felhound.y << delim;
	ret << gs.elves.size() << delim;
	for(int i=0;i<gs.elves.size();i++) {
		ret << gs.elves[i].x << delim;
		ret << gs.elves[i].y << delim;
		ret << gs.elves[i].id << delim;
	}
	
	return ret.str();
}


std::string gameStateToString(const GameState& gs) {
	stringstream ret;
	ret << "{GameState:\n";
	ret << "{FH: pos=";
	ret << "(" << gs.felhound.x << "," << gs.felhound.y << ")}\n";
	ret << gs.elves.size() << "Elves:\n";
	for(int i=0;i<gs.elves.size();i++) {
		ret << "[";
		ret << "id=" << gs.elves[i].id << ", ";
		ret << "pos=(" << gs.elves[i].x << ", " << gs.elves[i].y << ")";
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
	int n; read >> n;
	std::cout << n << std::endl;

	for(int i=0;i<n;i++) {
		Elf e;
		read >> e.x;
		read >> e.y;
		read >> e.id;
		ret.elves.push_back(e);
	}
	
	return ret;
}