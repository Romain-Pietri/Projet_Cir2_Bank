 -ptjCC=gcc
CFLAGS=-I.

SRC_DIR=./src
OBJ_DIR=./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

main.exe: $(OBJ_FILES) 
	g++ $(LDFLAGS)-lm  -o $@   $^ -lsfml-graphics -lsfml-window -lsfml-system -lpthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p obj
	g++ $(CFLAGS) -c -lm  -o  $@  $< -lsfml-graphics -lsfml-window -lsfml-system -lpthread 