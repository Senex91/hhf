
.PHONY:
main:
	cd shared && $(MAKE)
	cd client && $(MAKE)
	cd server && $(MAKE)

%.o: %.cpp
	g++ $(CFLAGS) $< -o $(OBJ_HOME)/$@ -g



.PHONY: clean
clean:
	rm *.o
