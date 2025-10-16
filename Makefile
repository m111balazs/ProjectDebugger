CC = gcc
CFLAGS = -IC:/Dev/SDL3-3.2.24/x86_64-w64-mingw32/include
LDFLAGS = -LC:/Dev/SDL3-3.2.24/x86_64-w64-mingw32/lib -lSDL3 -mwindows

all:
	$(CC) main.c -o build/game.exe $(CFLAGS) $(LDFLAGS)

clean:
	rm -f build/game.exe

run: all
	./build/game.exe