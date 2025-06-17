CC = gcc
ROOT_DIR = ~/Desktop/OpenGL
CFLAGS = -I $(ROOT_DIR)/ThirdParty
LDFLAGS = -lGL -lglfw 
SRC = main.cpp glad.c utils.cpp events.c

all: $(SRC) 
	$(CXX) -o main $(CFLAGS) $(SRC) $(LDFLAGS)

run: main
	./main

clean: 
	@rm main
