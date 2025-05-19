@echo off
chcp 65001

echo Building support utilities...

REM Building bmp2c
cd support/bmp2c
/c/msys64/msys2_shell.cmd -mingw64 -defterm -here -no-start -c "g++ -o bmp2c.exe bmp2c.cpp -I.."
cd ../..

REM Building encyclopedia2c
cd support/encyclopedia2c
/c/msys64/msys2_shell.cmd -mingw64 -defterm -here -no-start -c "g++ -o encyclopedia2c.exe encyclopedia2c.cpp stdafx.cpp -I.."
cd ../..

REM Building enummaker
cd support/enummaker
/c/msys64/msys2_shell.cmd -mingw64 -defterm -here -no-start -c "g++ -o enummaker.exe enummaker.cpp -I.."
cd ../..

REM Building map2c
cd support/map2c
/c/msys64/msys2_shell.cmd -mingw64 -defterm -here -no-start -c "g++ -o map2c.exe map2c.cpp -I.."
cd ../..

REM Building txt2c
cd support/txt2c
/c/msys64/msys2_shell.cmd -mingw64 -defterm -here -no-start -c "g++ -o txt2c.exe txt2c.cpp -I.."
cd ../..

REM Building tile2c
cd support/tile2c
/c/msys64/msys2_shell.cmd -mingw64 -defterm -here -no-start -c "g++ -o tile2c.exe tile2c.cpp -I.."
cd ../..

echo Generating files...

REM Generating glbdef.h
cd support/enummaker
./enummaker.exe ../../source.txt
cd ../..

REM Generating encyclopedia.h
cd support/encyclopedia2c
./encyclopedia2c.exe ../../encyclopedia.txt
cd ../..

echo Building main project...

REM Building main project
/c/msys64/msys2_shell.cmd -mingw64 -defterm -here -no-start -c "g++ -o powder.exe *.cpp gfx/*.cpp rooms/*.cpp -I. -Iport/sdl -IC:/msys64/mingw64/include/SDL2 -LC:/msys64/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -O2 -Wall -std=c++11 -D_WIN32 -D_WINDOWS"

if %ERRORLEVEL% EQU 0 (
    echo Build successful!
    echo The executable is: powder.exe
) else (
    echo Build failed!
) 