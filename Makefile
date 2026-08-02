CC = gcc
CFLAGS = -Wall -Wextra -Iinclude `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lm

SRC = src/main.c src/game.c src/player.c


TARGET = build/zombie-survival

all:
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf build