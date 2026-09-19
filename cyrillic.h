#ifndef CYRILLIC_H
#define CYRILLIC_H

#include "mygba.h"

typedef u32 GFX_CODEPOINT;

bool is_cyrillic(GFX_CODEPOINT c);
u16 gfx_getcyrillictile(GFX_CODEPOINT c);

#endif // CYRILLIC_H
