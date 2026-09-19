#ifndef CYRILLIC_H
#define CYRILLIC_H

#include "mygba.h"

typedef u32 GFX_CODEPOINT;

// The checked-in atlas contains one vertical column of 20x20 pixel glyphs.
#define CYRILLIC_WIDTH 20
#define CYRILLIC_HEIGHT 20
#define CYRILLIC_GLYPH_COUNT 66

bool is_cyrillic(GFX_CODEPOINT c);
u16 gfx_getcyrillictile(GFX_CODEPOINT c);

#endif // CYRILLIC_H
