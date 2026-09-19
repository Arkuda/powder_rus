#ifndef CYRILLIC_H
#define CYRILLIC_H

#include "mygba.h"

// gfx/cyrillic.bmp stores 66 vertically stacked 20x20 RGB555 glyphs.
#define CYRILLIC_WIDTH 20
#define CYRILLIC_HEIGHT 20
#define CYRILLIC_GLYPH_COUNT 66

// Функция для проверки, является ли символ кириллическим
bool is_cyrillic(char c);

// Функция для получения тайла кириллического символа
u16 gfx_getcyrillictile(char c);

#endif // CYRILLIC_H
