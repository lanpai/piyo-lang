BINARY = piyo-lang

CPP_STD=c++17

BUILD_DIR = build
OBJ_DIR = obj

LIB =

ifeq ($(OS),Windows_NT)
	LIB =
	BINARY := $(BINARY).exe
	RUN_PREFIX = start
endif

output: main.o Interpreter.o Value.o
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); $(CXX) -Wall -std=$(CPP_STD) main.o Interpreter.o Value.o -o ../$(BUILD_DIR)/$(BINARY) $(LIB)

main.o: main.cpp
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); $(CXX) -Wall -std=$(CPP_STD) -c ../main.cpp

Interpreter.o: Interpreter.cpp
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); $(CXX) -Wall -std=$(CPP_STD) -c ../Interpreter.cpp

Value.o: Types/Value.cpp
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); $(CXX) -Wall -std=$(CPP_STD) -c ../Types/Value.cpp

run:
	$(RUN_PREFIX) $(BUILD_DIR)/$(BINARY)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
