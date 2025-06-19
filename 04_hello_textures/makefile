CC = gcc
ROOT_DIR = ~/Desktop/OpenGL
CFLAGS = -I $(ROOT_DIR)/ThirdParty/include
LDFLAGS = -lGL -lglfw 
SRC = main.cpp utils.cpp events.c \
      $(ROOT_DIR)/ThirdParty/src/glad.c

all: $(SRC) 
	@ $(CXX) -o main $(CFLAGS) $(SRC) $(LDFLAGS)

run: main
	@./main

clean: 
	@rm main
