OBJECTS := $(wildcard *.o)
SHARED_OBJS = $(wildcard $(OBJ_HOME)/shared/*.o)
EXECUTABLES := $(OBJECTS:.o=)


.PHONY: main
main: $(EXECUTABLES)
	

% : %.o
	g++ -o $@ $< $(LINK_FILES) $(SHARED_OBJS)