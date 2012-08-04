// CommandTestSuite.h
#include <cxxtest/TestSuite.h>
#include "Command.h"

class CommandTestSuite : public CxxTest::TestSuite {
public:
	void testJoinCommand(void) {
		JoinCommand c;
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
	void testIDCommand() {
		IDCommand c(1);
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
	void testMoveCommand() {
		MoveCommand c(1,1);
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
	void testBlinkCommand() {
		BlinkCommand c(1,1);
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
	void testGameStateCommand() {
		std::vector<Elf> elves;
		elves.push_back((Elf) {1, 0, 0, 0, 0});
		elves.push_back((Elf) {2, 0, 1, 0, 0});
		elves.push_back((Elf) {3, 1, 0, 0, 0});
		GameState state1;
		state1.elves = elves;
		state1.felhound = (Felhound) {2,2, 0, 0};
		state1.orb.x = 0;
		state1.orb.y = 0;
		state1.orb.id = -1;
		
		TS_WARN(state1.orb.x);
		TS_WARN(state1.orb.y);
		TS_WARN(state1.orb.id);
		TS_WARN(gameStateToString(state1));
		
		GameStateCommand c(state1);
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_WARN(out);
		TS_WARN(out2);
		TS_ASSERT(out == out2);
	}
};