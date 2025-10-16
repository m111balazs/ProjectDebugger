@echo off
set SDL_PATH=C:\Dev\SDL3-3.2.24\x86_64-w64-mingw32

echo Building...
gcc main.c -I%SDL_PATH%\include -L%SDL_PATH%\lib -lSDL3 -mwindows -o build\game.exe

if %errorlevel% neq 0 (
    echo ❌ Build failed!
    pause
    exit /b 1
)

echo ✅ Build succeeded!
echo Running game...
build\game.exe
pause