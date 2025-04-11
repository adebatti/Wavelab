# Makefile for WaveLab on macOS (Homebrew setup)

CC = gcc
CFLAGS = -std=c89 -pedantic -Wall \
	-I./src \
	-I./third_party \
	-I./raygui \
	-I/opt/homebrew/opt/raylib/include

LDFLAGS = -L/opt/homebrew/opt/raylib/lib \
	-lraylib -lm \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo

SRC = src/main.c src/audio.c src/filters.c src/ui.c src/wave.c
OBJ = $(SRC:.c=.o) third_party/miniaudio_impl.o
TARGET = WaveLab

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

third_party/miniaudio_impl.o: third_party/miniaudio_impl.c
	$(CC) -std=c99 -pedantic -Wall -I./src -I./third_party -I./raygui -I/opt/homebrew/opt/raylib/include -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
