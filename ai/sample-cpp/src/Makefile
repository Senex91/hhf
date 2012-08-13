SOURCES := $(wildcard *.cpp)
OBJECT_NAMES := $(SOURCES:.cpp=.o)
OBJECTS := $(addprefix $(OBJ_DIR)/,$(OBJECT_NAMES))
HEADERS := $(wildcard $(INCL_DIR)*.h)

.PHONY: main
main: $(OBJECTS)
	echo $(OBJECTS)

$(OBJ_DIR)/%.o : %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $< -o $@ $(INCLUDE_DIRS)