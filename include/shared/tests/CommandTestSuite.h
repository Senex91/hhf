// CommandTestSuite.h
#include <cxxtest/TestSuite.h>
#include "Command.h"

class CommandTestSuite : public CxxTest::TestSuite {
public:
	void testJoinCommand(void) {
		initializeCommand();
		
		JoinCommand c;
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
	void testIDCommand() {
		initializeCommand();
		
		IDCommand c(1);
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
	void testMoveCommand() {
		initializeCommand();
		
		MoveCommand c(1,1);
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
	void testBlinkCommand() {
		initializeCommand();
		
		BlinkCommand c(1,1);
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
	void testGameStateCommand() {
		initializeCommand();
		
		std::vector<Elf> elves;
		elves.push_back((Elf) {1, 0, 0, 0, 0});
		elves.push_back((Elf) {2, 0, 1, 0, 0});
		elves.push_back((Elf) {3, 1, 0, 0, 0});
		GameState state1;
		state1.elves = elves;
		state1.felhound = (Felhound) {2,2, 0, 0};
		
		GameStateCommand c(state1);
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
};