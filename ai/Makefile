SUBFOLDERS = $(subst ./Makefile,,$(wildcard ./*))
THISDIR := $(realpath .)

.PHONY: all
all: 
	$(foreach SUBFOLDER,$(SUBFOLDERS),cd $(SUBFOLDER) && $(MAKE) && cd $(THISDIR) &&) true
	
.PHONY: clean
clean:
	$(foreach SUBFOLDER,$(SUBFOLDERS),cd $(SUBFOLDER) && $(MAKE) clean && cd $(THISDIR) &&) true
