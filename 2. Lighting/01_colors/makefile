# Compiler and flags
CXX = g++
CC = gcc
ROOT_DIR = $(HOME)/Desktop/OpenGL
CFLAGS = -I$(ROOT_DIR)/ThirdParty/include -Iinclude
LDFLAGS = -L$(ROOT_DIR)/ThirdParty/lib -lGL -lglfw

# Source and object files
SRC = src/main.cpp \
      src/utils.cpp \
      src/events.cpp \
      $(ROOT_DIR)/ThirdParty/src/glad.c \
      src/object.cpp \
      src/vertex.cpp \
	  src/camera.cpp

# Convert each src/*.cpp or *.c to bin/*.o
OBJ = $(patsubst src/%.cpp, bin/%.o, \
      $(patsubst $(ROOT_DIR)/ThirdParty/src/%.c, bin/%.o, \
      $(filter %.cpp %.c, $(SRC))))

# Default target
all: main

# Link object files to create executable
main: $(OBJ)
	@echo Linking...
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

# Compile .cpp/.c files into .o files in bin/
bin/%.o: src/%.cpp
	@$(CXX) -c $< -o $@ $(CFLAGS)

bin/%.o: src/%.c
	@$(CC) -c $< -o $@ $(CFLAGS)

bin/%.o: $(ROOT_DIR)/ThirdParty/src/%.c
	@$(CC) -c $< -o $@ $(CFLAGS)

# Debug build
gdb: CFLAGS += -g
gdb: main

# Run the executable
run: main
	@./main

# Clean build artifacts
clean:
	@rm -rf bin/* main
