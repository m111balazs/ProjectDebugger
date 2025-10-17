@echo off
set SDL_PATH=C:\Dev\SDL3-3.2.24\x86_64-w64-mingw32
set SDL_IMG_PATH=C:\Dev\SDL3_image-3.2.4\x86_64-w64-mingw32

echo Building...
gcc game/src/main.c -I%SDL_PATH%\include -I%SDL_IMG_PATH%\include ^
-L%SDL_PATH%\bin -L%SDL_IMG_PATH%\bin ^
-lSDL3_image -lSDL3 -mwindows -o build\game.exe

if %errorlevel% neq 0 (
    echo ❌ Build failed!
) else (
    echo ✅ Build succeeded!
    echo Running game...
    copy /Y "%SDL_PATH%\bin\SDL3.dll" "build\"
    copy /Y "%SDL_IMG_PATH%\bin\SDL3_image.dll" "build\"
    build\game.exe
)
pause
