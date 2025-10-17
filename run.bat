@echo off
title Building Game...
echo ==============================
echo Compiling SDL3 Game Project
echo ==============================

set COMPILER=C:\mingw64\bin\gcc.exe
set SDL_PATH=C:\Dev\SDL3-3.2.24\x86_64-w64-mingw32
set SDL_IMG_PATH=C:\Dev\SDL3_image-3.2.4\x86_64-w64-mingw32
set INCLUDE_PATHS=-Isrc -Isrc/core -I"%SDL_PATH%\include" -I"%SDL_IMG_PATH%\include"
set LIB_PATHS=-L"%SDL_PATH%\lib" -L"%SDL_IMG_PATH%\lib"
set LIBS=-lSDL3 -lSDL3_image

set SRC_FILES=src\main.c src\core\engine.c src\core\input.c src\graphics\texture.c src\graphics\animation.c src\game\tilemap.c
set OUT_FILE=build\game.exe

echo.
echo Compiling...
%COMPILER% %SRC_FILES% %INCLUDE_PATHS% %LIB_PATHS% %LIBS% -o %OUT_FILE%

if %errorlevel% neq 0 (
    echo.
    echo Build failed!
    pause
    exit /b %errorlevel%
)

echo.
echo Build succeeded!
echo Running...
echo ==============================
echo.
%OUT_FILE%

echo.
pause
