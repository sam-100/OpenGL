CC = gcc
ROOT_DIR = ~/Desktop/OpenGL
CFLAGS = -I $(ROOT_DIR)/ThirdParty
LDFLAGS = -lGL -lglfw 
SRC = main.c

all: $(SRC)
	$(CC) -o main $(CFLAGS) $(SRC) $(LDFLAGS)

run: main
	./main

clean: 
	@rm main
