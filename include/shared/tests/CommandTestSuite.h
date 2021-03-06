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
		std::map<int,Elf> elves;
		elves[0] = ((Elf) {1, 0, 0, 0, 0, 0.0f, 0.1, 0.2, (ElfColor){1.0f,0.0f,0.0f}, ELF_UNSPAWNED});
		elves[1] = ((Elf) {2, 0, 1, 0, 0, 1.0f, 0.3, 0.4, (ElfColor){0.0f,1.0f,0.0f}, ELF_SPAWNED});
		elves[2] = ((Elf) {3, 1, 0, 0, 0, 2.0f, 0.5, 0.6, (ElfColor){0.0f,0.0f,1.0f}, ELF_DEAD});
		GameState state1;
		state1.elves = elves;
		state1.felhound = (Felhound) {2, 2, 0, 0, 1.0, FELHOUND_RESTING};
		state1.orb.x = 0;
		state1.orb.y = 0;
		state1.orb.id = -1;
		state1.orb.state = ORB_UNSPAWNED;
		
		
		GameStateCommand c(state1);
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
	void testThrowCommand() {
		ThrowCommand c(1);
		std::string out = c.write();
		TS_ASSERT(out != "");
		Command* deser = Command::deserialize(out);
		TS_ASSERT(deser != NULL);
		std::string out2 = deser->write();
		TS_ASSERT(out == out2);
	}
};