OBJECTS := $(wildcard *.o)
SHARED_OBJS = $(wildcard $(OBJ_HOME)/shared/*.o)
EXECUTABLES := $(OBJECTS:.o=.test)


.PHONY: main
main: $(EXECUTABLES)
	

%.test : %.o
	g++ -o $@ $< $(LINK_FILES) $(SHARED_OBJS)