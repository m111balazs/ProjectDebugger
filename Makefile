# === CONFIG ===
CC = gcc
CFLAGS = -Wall -I src -I C:\Dev\SDL3-3.2.24\x86_64-w64-mingw32\include
LDFLAGS = -L C:\Dev\SDL3-3.2.24\x86_64-w64-mingw32\lib -lSDL3 -lSDL3_image
SRC = $(wildcard src/*.c src/core/*.c src/graphics/*.c src/game/*.c)
OBJ = $(SRC:.c=.o)
TARGET = game.exe

# === BUILD RULES ===
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

clean:
	del /Q $(OBJ) $(TARGET)
