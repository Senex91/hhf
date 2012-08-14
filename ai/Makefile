SUBDIRS = $(subst Makefile,,$(wildcard *))
THISDIR := $(realpath .)

.PHONY: all $(SUBDIRS)
all: $(SUBDIRS)
	

$(SUBDIRS):
	cd $@ && $(MAKE) $(MAKECMDGOALS)

.PHONY: clean
clean: $(SUBDIRS)
	
