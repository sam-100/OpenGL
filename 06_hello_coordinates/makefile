CC = gcc
ROOT_DIR = ~/Desktop/OpenGL
CFLAGS = -I $(ROOT_DIR)/ThirdParty/include -I include
LDFLAGS = -L $(ROOT_DIR)/ThirdParty/lib -lGL -lglfw
SRC = 	src/main.cpp \
		src/utils.cpp \
		src/events.c \
      	$(ROOT_DIR)/ThirdParty/src/glad.c \
		src/object.cpp

all: $(SRC) 
	@ $(CXX) -o main $(CFLAGS) $(SRC) $(LDFLAGS)

gdb: CFLAGS += -g
gdb: all

run: main
	@./main

clean: 
	@rm main
