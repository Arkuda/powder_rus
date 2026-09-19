#!/usr/bin/env python3
"""Static consistency checks for the Cyrillic atlas and its consumers."""

import re
from pathlib import Path

from create_cyrillic_font import CELL_HEIGHT, CELL_WIDTH, GLYPHS, read_bmp
from create_cyrillic_indexed_font import render as render_indexed


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
mapping = re.search(r"glb_cyrillic_codepoints\[\]\s*=\s*\{(.*?)\};", engine, re.S)
assert mapping, "missing Unicode glyph map"
entries = re.findall(r"0x[0-9a-fA-F]+", mapping.group(1))
assert len(entries) == cells, f"C++ map has {len(entries)} entries, atlas has {cells} cells"
assert '#include "gfx/cyrillic_8.c"' in engine, \
    "Cyrillic renderer must include the indexed 8x8 glyph atlas"
atlas = (ROOT / "gfx/cyrillic_8.c").read_text(encoding="utf-8")
assert "cyrillic_8_Tiles[66 * 8 * 8]" in atlas, \
    "Indexed Cyrillic atlas must contain 66 8x8 glyphs"
assert "cyrillic_10_Tiles[66 * 10 * 10]" in atlas, \
    "Indexed Cyrillic atlas must contain 66 10x10 glyphs"
assert (ROOT / "gfx/cyrillic_8.c").read_text(encoding="utf-8") == \
    render_indexed(ROOT / "gfx/cyrillic.bmp")
generator = (ROOT / "create_cyrillic_indexed_font.py").read_text(encoding="utf-8")
assert "Image.Resampling.BOX" in generator
assert "COVERAGE_BRIGHTNESS_THRESHOLD" in generator

print(f"Cyrillic atlas: {width}x{height}, {cells} glyphs, layout and addressing are consistent")
