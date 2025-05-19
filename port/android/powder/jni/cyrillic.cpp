#include "cyrillic.h"

// Функция для проверки, является ли символ кириллическим
bool is_cyrillic(char c) {
    unsigned char uc = (unsigned char)c;
    return (uc >= 0xD0 && uc <= 0xDF) || (uc >= 0xE0 && uc <= 0xEF);
}

// Функция для получения тайла кириллического символа
u16 gfx_getcyrillictile(char c) {
    if (!is_cyrillic(c)) return INVALID_TILEIDX;
    
    // Преобразуем символ в индекс в кириллическом шрифте
    unsigned char uc = (unsigned char)c;
    int idx = uc - 0xD0;  // Начинаем с 0xD0 для кириллицы
    return idx;
} 