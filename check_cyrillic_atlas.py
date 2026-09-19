#!/usr/bin/env python3
"""Static consistency checks for the Cyrillic atlas and its consumers."""

import re
from pathlib import Path

from create_cyrillic_font import CELL_HEIGHT, CELL_WIDTH, GLYPHS, read_bmp


ROOT = Path(__file__).resolve().parent
width, height, _ = read_bmp(ROOT / "gfx/cyrillic.bmp")
cells, remainder = divmod(width * height, CELL_WIDTH * CELL_HEIGHT)
assert remainder == 0, "atlas dimensions do not contain whole cells"
assert width == CELL_WIDTH, "bmp2c scan-line output requires a one-column atlas"
assert cells == len(GLYPHS), f"Unicode map has {len(GLYPHS)} entries, atlas has {cells} cells"

header = (ROOT / "cyrillic.h").read_text(encoding="utf-8")
assert f"CYRILLIC_GLYPH_COUNT {len(GLYPHS)}" in header
assert f"CYRILLIC_WIDTH {CELL_WIDTH}" in header
assert f"CYRILLIC_HEIGHT {CELL_HEIGHT}" in header

engine = (ROOT / "gfxengine.cpp").read_text(encoding="utf-8")
mapping = re.search(r"cyrillic_cp1251\[CYRILLIC_GLYPH_COUNT\]\s*=\s*\{(.*?)\};", engine, re.S)
assert mapping, "missing CP1251 Unicode map"
entries = re.findall(r"0x[0-9a-fA-F]+", mapping.group(1))
assert len(entries) == cells, f"C++ map has {len(entries)} entries, atlas has {cells} cells"
assert "((const u16 *)glb_tilesets[glb_tileset].cyrillic) +" in engine, \
    "Cyrillic address must use bmp2c's unsigned-short pixel format"

print(f"Cyrillic atlas: {width}x{height}, {cells} glyphs, layout and addressing are consistent")
