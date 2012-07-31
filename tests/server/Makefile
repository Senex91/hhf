FOLDER := server/
OBJECTS := $(wildcard *.o)
MY_OBJS = $(subst $(OBJ_HOME)/$(FOLDER)main.o,,$(wildcard $(OBJ_HOME)/$(FOLDER)*.o))
SHARED_OBJS = $(OBJ_HOME)/shared/,,($wildcard $(OBJ_HOME)/shared/*.o))
EXECUTABLES := $(OBJECTS:.o=)


.PHONY: main
main: $(EXECUTABLES)
	

% : %.o
	g++ -o $@ $< $(LINK_FILES) $(MY_OBJS) $(SHARED_OBJS)