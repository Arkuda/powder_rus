#include "cyrillic.h"

// Single-byte Cyrillic (CP1251) range used by the bitmap font.
bool is_cyrillic(char c) {
    unsigned char uc = (unsigned char)c;
    return (uc >= 0xC0 && uc <= 0xFF);
}

u16 gfx_getcyrillictile(char c) {
    unsigned char uc = (unsigned char)c;
    int idx;

    if (!is_cyrillic(c))
        return INVALID_TILEIDX;

    idx = (int) uc - 0xC0;
    if (idx < 0 || idx >= 70)
        return INVALID_TILEIDX;

    return (u16) idx;
}
