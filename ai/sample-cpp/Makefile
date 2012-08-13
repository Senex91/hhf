export INCLUDE_DIRS := -I/usr/include/SDL/ -I$(realpath include) -I$(INCL_HOME)/shared/ 
export OBJ_DIR := $(realpath obj)
export INCL_DIR := $(realpath include)
LINK_FILES := -lSDL -lSDL_net $(wildcard $(COURT_ICHIRO_HOME)/obj/shared/*.o) -Wl,-R/usr/lib/
export CFLAGS := -Wall -c
EXECUTABLE := courtIchiroSampleAI
CXX := g++

.PHONY: main
main:
	cd src && $(MAKE)
	$(CXX) -o $(EXECUTABLE) obj/*.o $(LINK_FILES)

.PHONY: clean
clean:
	rm obj/*.o
	rm $(EXECUTABLE)