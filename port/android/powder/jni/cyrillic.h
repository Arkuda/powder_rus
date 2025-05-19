#ifndef CYRILLIC_H
#define CYRILLIC_H

#include "mygba.h"

// Константа для недопустимого индекса тайла
#define INVALID_TILEIDX 0xFFFF

// Функция для проверки, является ли символ кириллическим
bool is_cyrillic(char c);

// Функция для получения тайла кириллического символа
u16 gfx_getcyrillictile(char c);

#endif // CYRILLIC_H 