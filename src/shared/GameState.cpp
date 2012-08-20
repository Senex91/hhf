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
	orb = other.orb;
}

const GameState& GameState::operator=(const GameState& other){
	elves = other.elves;
	felhound = other.felhound;
	orb = other.orb;
	return *this;
}

std::string serializeGameState(const GameState& gs) {
	static string delim = " ";
	stringstream ret;
	ret << gs.orb.x << delim;
	ret << gs.orb.y << delim;
	ret << gs.orb.id << delim;
	ret << gs.orb.alive << delim;
	ret << gs.felhound.x << delim;
	ret << gs.felhound.y << delim;
	ret << gs.felhound.xvel << delim;
	ret << gs.felhound.yvel << delim;
	ret << gs.felhound.orientation << delim;
	ret << gs.felhound.alive << delim;
	ret << gs.elves.size() << delim;
	for(unsigned int i=0;i<gs.elves.size();i++) {
		ret << gs.elves[i].x << delim;
		ret << gs.elves[i].y << delim;
		ret << gs.elves[i].xvel << delim;
		ret << gs.elves[i].yvel << delim;
		ret << gs.elves[i].orientation << delim;
		ret << gs.elves[i].xgoal << delim;
		ret << gs.elves[i].ygoal << delim;
		ret << gs.elves[i].id << delim;
		ret << gs.elves[i].color.r << delim;
		ret << gs.elves[i].color.g << delim;
		ret << gs.elves[i].color.b << delim;
		ret << gs.elves[i].alive << delim;
	}
	
	return ret.str();
}


std::string gameStateToString(const GameState& gs) {
	stringstream ret;
	ret << "{GameState:\n";
	ret << "{FH: pos=";
	ret << "(" << gs.felhound.x << "," << gs.felhound.y << "), vel=(" << gs.felhound.xvel << "," << gs.felhound.yvel << "), orientation=" << gs.felhound.orientation << " }\n";
	ret << "{Orb: pos=(" << gs.orb.x << ", " << gs.orb.y << "), id=" << gs.orb.id << ", alive=" << gs.orb.alive <<"}\n";
	ret << gs.elves.size() << "Elves:\n";
	for(unsigned int i=0;i<gs.elves.size();i++) {
		ret << "[";
		ret << "id=" << gs.elves[i].id << ", ";
		ret << "pos=(" << gs.elves[i].x << ", " << gs.elves[i].y << "), ";
		ret << "vel=(" << gs.elves[i].xvel << ", " << gs.elves[i].yvel << ")";
		ret << "orientation=(" << gs.elves[i].orientation << ")";
		ret << "goal=(" << gs.elves[i].xgoal << ", " << gs.elves[i].ygoal << ")";
		ret << "color=(" << gs.elves[i].color.r << ", " << gs.elves[i].color.g << ", " << gs.elves[i].color.b << ")";
		ret << "alive=" << gs.elves[i].alive << "";
		ret << "]\n";
	}
	ret << "}";
	
	return ret.str();
}
GameState deserializeGameState(const std::string& str) {
	GameState ret;
	stringstream read(str);
	read >> ret.orb.x;
	read >> ret.orb.y;
	read >> ret.orb.id;
	read >> ret.orb.alive;
	read >> ret.felhound.x;
	read >> ret.felhound.y;
	read >> ret.felhound.xvel;
	read >> ret.felhound.yvel;
	read >> ret.felhound.orientation;
	read >> ret.felhound.alive;
	int n; read >> n;
	
	for(int i=0;i<n;i++) {
		Elf e;
		read >> e.x;
		read >> e.y;
		read >> e.xvel;
		read >> e.yvel;
		read >> e.orientation;
		read >> e.xgoal;
		read >> e.ygoal;
		read >> e.id;
		read >> e.color.r;
		read >> e.color.g;
		read >> e.color.b;
		read >> e.alive;
		ret.elves.push_back(e);
	}
	
	return ret;
}