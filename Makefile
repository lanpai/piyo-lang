BINARY = piyo-lang

CPP_STD=c++17

OBJS_C =
OBJS = main.o LangParser.o

BUILD_DIR = build
OBJ_DIR = obj

LIB =

ifeq ($(OS),Windows_NT)
	LIB =
	BINARY := $(BINARY).exe
	RUN_PREFIX = start
endif

output: $(OBJS_C) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); $(CXX) -Wall -std=$(CPP_STD) $(OBJS) -o ../$(BUILD_DIR)/$(BINARY) $(LIB)

$(OBJS): %.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	cd $(OBJ_DIR); $(CXX) -Wall -std=$(CPP_STD) -c ../$< $(LIB)

run:
	$(RUN_PREFIX) $(BUILD_DIR)/$(BINARY)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
