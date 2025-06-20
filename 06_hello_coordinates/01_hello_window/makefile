CC = gcc
CXX = g++
ROOT_DIR = ~/Desktop/OpenGL
CFLAGS = -I $(ROOT_DIR)/ThirdParty/include
LDFLAGS = -lGL -lglfw 
SRC = main.c utils.c events.c \
	$(ROOT_DIR)/ThirdParty/src/glad.c

all: $(SRC)
	$(CC) -o main $(CFLAGS) $(SRC) $(LDFLAGS)

run: main
	./main

clean: 
	@rm main
