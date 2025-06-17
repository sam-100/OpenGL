CC = gcc
ROOT_DIR = ~/Desktop/OpenGL
CFLAGS = -I $(ROOT_DIR)/ThirdParty
LDFLAGS = -lGL -lglfw 
SRC = main.c glad.c utils.c events.c

all: main.c glad.c 
	$(CC) -o main $(CFLAGS) $(SRC) $(LDFLAGS)

run: main
	./main

clean: 
	@rm main
