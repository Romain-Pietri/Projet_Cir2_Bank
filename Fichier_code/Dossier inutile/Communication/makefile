CC=gcc
CFLAGS=-I.

SRC_DIR=./src
OBJ_DIR=./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

main.exe: $(OBJ_FILES) 
	g++ $(LDFLAGS)-lm  -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p obj
	g++ $(CFLAGS) -c -lm -o $@ $<