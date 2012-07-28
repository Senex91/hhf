CC := g++
LINK_FILES := -L/usr/local/lib/ -L/usr/lib/ -lCEGUIBase -lCEGUIOgreRenderer -lOgreTerrain -lOgreMain -lpthread -lboost_system -lGL -lOgreMain -lOIS -Wl,-R/usr/local/lib/ 
export OBJ_HOME = $(realpath obj)
export INCL_HOME = $(realpath include)
CLIENT := courtIchiroClient
SERVER := courtIchiroServer

.PHONY: main 
main: 
	cd src && $(MAKE)
	$(CC) -Wall obj/shared/*.o obj/client/*.o -o $(CLIENT) $(LINK_FILES)
	$(CC) -Wall obj/shared/*.o obj/server/*.o -o $(SERVER) $(LINK_FILES)

.PHONY: clean
clean: 
	rm -f obj/*/*.o
	rm -f $(CLIENT)
	rm -f $(SERVER)
