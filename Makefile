CC := g++
LINK_FILES := -L/usr/local/lib/ -L/usr/lib/ -lCEGUIBase -lCEGUIOgreRenderer -lOgreTerrain -lOgreMain -lpthread -lboost_system -lGL -lOgreMain -lOIS -Wl,-R/usr/local/lib/ 
export OBJ_HOME = $(realpath obj)
export INCL_HOME = $(realpath include)
EXECUTABLE := main

.PHONY: main 
main: 
	cd src && $(MAKE)
	$(CC) -Wall obj/*.o -o courtIchiro $(LINK_FILES) 

.PHONY: clean
clean: 
	rm -f obj/*.o
	rm -f $(EXECUTABLE)
