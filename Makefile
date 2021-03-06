export CXX := g++
export LINK_FILES := -L/usr/local/lib/ -L/usr/lib/ -lCEGUIBase -lCEGUIOgreRenderer -lOgreTerrain -lOgreMain -lpthread -lboost_system -lGL -lOgreMain -lOIS -lSDL -lSDL_net -Wl,-R/usr/local/lib/ 
export COURT_ICHIRO_HOME := $(realpath .)
export OBJ_HOME = $(realpath obj)
export INCL_HOME = $(realpath include)
export TEST_HOME = $(realpath tests)
CLIENT := courtIchiroClient
SERVER := courtIchiroServer

.PHONY: main
main: executables tests ai


.PHONY: executables
executables:
	cd src && $(MAKE)
	$(CXX) -Wall obj/shared/*.o obj/client/*.o -o $(CLIENT) $(LINK_FILES)
	$(CXX) -Wall obj/shared/*.o obj/server/*.o -o $(SERVER) $(LINK_FILES)

.PHONY: tests
tests: executables
	cd src && $(MAKE) tests
	cd tests && $(MAKE)

.PHONY: ai
ai: executables
	cd ai && $(MAKE)

.PHONY: clean
clean: 
	rm -f obj/*/*.o
	rm -f $(CLIENT)
	rm -f $(SERVER)
	rm -f tests/*/*.o
	cd ai && $(MAKE) clean