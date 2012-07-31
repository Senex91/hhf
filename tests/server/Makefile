FOLDER := server/
OBJECTS := $(wildcard *.o)
MY_OBJS = $(subst $(OBJ_HOME)/$(FOLDER)main.o,,$(wildcard $(OBJ_HOME)/$(FOLDER)*.o))
SHARED_OBJS = $(wildcard $(OBJ_HOME)/shared/*.o)
EXECUTABLES := $(OBJECTS:.o=.test)


.PHONY: main
main: $(EXECUTABLES)
	

%.test : %.o
	g++ -o $@ $< $(LINK_FILES) $(MY_OBJS) $(SHARED_OBJS)