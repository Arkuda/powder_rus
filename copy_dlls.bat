@echo off
echo Копирование DLL файлов SDL2...

copy "C:\msys64\mingw64\bin\SDL2.dll" .
copy "C:\msys64\mingw64\bin\SDL2_image.dll" .
copy "C:\msys64\mingw64\bin\SDL2_ttf.dll" .

echo Готово! 