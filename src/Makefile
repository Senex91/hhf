CC := g++
INCLUDES := -I/usr/local/include/CEGUI/ -I/usr/include/OGRE/ -I/usr/include/OIS/ -I$(INCL_HOME)
CFLAGS := -Wall -c $(INCLUDES) -O3
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

main: $(OBJECTS)
	

%.o: %.cpp
	g++ $(CFLAGS) $< -o $(OBJ_HOME)/$@ -g



.PHONY: clean
clean:
	rm *.o
