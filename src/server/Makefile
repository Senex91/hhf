CC := g++
INCLUDES := -I/usr/local/include/CEGUI/ -I/usr/include/OGRE/ -I/usr/include/OIS/ -I/usr/include/SDL/ -I$(INCL_HOME)/shared/ -I$(INCL_HOME)/shared/
CFLAGS := -Wall -c $(INCLUDES) -O3
SOURCES := $(wildcard *.cpp)
OBJECT_NAMES := $(SOURCES:.cpp=.o)
PREFIX := $(OBJ_HOME)/server/
OBJECTS := $(addprefix $(PREFIX),$(OBJECT_NAMES))

.PHONY:
main: $(OBJECTS)
	

$(PREFIX)%.o: %.cpp
	g++ $(CFLAGS) $< -o $@ -g



.PHONY: clean
clean:
	rm *.o
