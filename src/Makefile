
.PHONY: main
main:
	cd shared && $(MAKE)
	cd client && $(MAKE)
	cd server && $(MAKE)

.PHONY: tests
tests:
	cd shared && $(MAKE) tests
	cd client && $(MAKE) tests
	cd server && $(MAKE) tests

.PHONY: clean
clean:
	rm *.o
