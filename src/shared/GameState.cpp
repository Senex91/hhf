#include "GameState.h"
#include <sstream>

using std::stringstream;
using std::vector;
using std::string;

std::string serializeGameState(const GameState& gs) {
	stringstream ret;
	ret << gs.felhound.x << ",";
	ret << gs.felhound.y << ",";
	ret << gs.elves.size() << ",";
	for(int i=0;i<gs.elves.size();i++) {
		ret << gs.elves[i].x << ",";
		ret << gs.elves[i].y << ",";
		ret << gs.elves[i].id << ",";
	}
	
	return ret.str();
}
GameState deserializeGameState(const std::string& str) {
	GameState ret;
	stringstream read(str);
	read >> ret.felhound.x;
	read >> ret.felhound.y;
	int n; read >> n;
	for(int i=0;i<n;i++) {
		Elf e;
		read >> e.x;
		read >> e.y;
		read >> e.id;
		ret.elves.push_back(e);
	}
	
	return ret;
}