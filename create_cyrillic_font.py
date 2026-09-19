#!/usr/bin/env python3
"""Generate gfx/cyrillic.bmp.c from the canonical Cyrillic atlas.

The checked-in ``gfx/cyrillic.bmp`` is the single source of glyph pixels.  It
contains one vertical column of 20x20 cells in this exact Unicode order:

    абвгдеёжзийклмнопрстуфхцчшщъыьэюя
    АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ

Thus ё is cell 6 and Ё is cell 39 (zero based).  Keeping one column is
intentional: bmp2c emits scan-line pixels, not a tile-major array, so a glyph
is contiguous only when the atlas is a single cell wide.
"""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


CELL_WIDTH = 20
CELL_HEIGHT = 20
GLYPHS = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"


def read_bmp(path: Path) -> tuple[int, int, list[int]]:
    data = path.read_bytes()
    if data[:2] != b"BM" or len(data) < 54:
        raise ValueError(f"{path}: not a BMP file")
    offset = struct.unpack_from("<I", data, 10)[0]
    width, height, planes, bits, compression = struct.unpack_from("<iiHHI", data, 18)
    if width <= 0 or height <= 0 or planes != 1 or bits != 24 or compression != 0:
        raise ValueError(f"{path}: expected an uncompressed, bottom-up 24-bit BMP")
    stride = (width * 3 + 3) & ~3
    pixels: list[int] = []
    # Match support/bmp2c: convert bottom-up BMP rows into top-down RGB555.
    for y in range(height):
        row = offset + (height - 1 - y) * stride
        for x in range(width):
            blue, green, red = data[row + x * 3 : row + x * 3 + 3]
            pixels.append(((blue >> 3) << 10) | ((green >> 3) << 5) | (red >> 3))
    return width, height, pixels


def render_c(source: Path, width: int, height: int, pixels: list[int]) -> str:
    expected = (CELL_WIDTH, CELL_HEIGHT * len(GLYPHS))
    if (width, height) != expected:
        raise ValueError(f"{source}: expected {expected[0]}x{expected[1]}, got {width}x{height}")
    lines = [
        "// Auto-generated .bmp file",
        "// DO NOT HAND EDIT",
        f"// Generated from {source.name}",
        "",
        f"const unsigned short bmp_cyrillic[{len(pixels)}] = {{",
    ]
    for start in range(0, len(pixels), 8):
        chunk = pixels[start : start + 8]
        values = []
        for index, pixel in enumerate(chunk, start):
            values.append(f"0x{pixel:04x}" + ("," if index < len(pixels) - 1 else ""))
        lines.append(" ".join(values) + (" " if start + 8 < len(pixels) else ""))
    lines.extend(["};", ""])
    return "\n".join(lines)


def main() -> int:
    root = Path(__file__).resolve().parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=root / "gfx/cyrillic.bmp")
    parser.add_argument("--output", type=Path, default=root / "gfx/cyrillic.bmp.c")
    parser.add_argument("--check", action="store_true", help="fail rather than update stale output")
    args = parser.parse_args()

    generated = render_c(args.source, *read_bmp(args.source))
    if args.check:
        if not args.output.exists() or args.output.read_text(encoding="utf-8") != generated:
            raise SystemExit(f"{args.output} is stale; run {Path(__file__).name}")
    else:
        args.output.write_text(generated, encoding="utf-8", newline="\n")
        print(f"Generated {args.output} from {args.source} ({len(GLYPHS)} glyphs)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
