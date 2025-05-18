@echo off
set PATH=%PATH%;C:\msys64\mingw64\bin

g++ -o powder.exe *.cpp -I. -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -O2 -Wall

if %ERRORLEVEL% EQU 0 (
    echo Build successful!
    echo The executable is: powder.exe
) else (
    echo Build failed!
) 