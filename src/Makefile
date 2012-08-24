
.PHONY: main
main: client server shared
	

.PHONY: client
client: shared
	cd client && $(MAKE)

.PHONY: server
server: shared
	cd server && $(MAKE)
	
.PHONY: shared
shared:
	cd shared && $(MAKE)

.PHONY: tests
tests:
	cd shared && $(MAKE) tests
	cd client && $(MAKE) tests
	cd server && $(MAKE) tests

.PHONY: clean
clean:
	rm *.o
