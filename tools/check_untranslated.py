#!/usr/bin/env python3
"""Reject new English user-visible literals (existing reviewed exceptions are listed)."""
import argparse, ast, json, pathlib, re, sys
ROOT = pathlib.Path(__file__).resolve().parents[1]
FILES = ('main.cpp','action.cpp','artifact.cpp','creature.cpp','item.cpp','map.cpp',
         'msg.cpp','piety.cpp','victory.cpp','glbdef.cpp','source.txt','encyclopedia.txt')
STRING = re.compile(r'"(?:\\.|[^"\\])*"')
ENGLISH = re.compile(r'[A-Za-z]{3,}')
TECHNICAL = re.compile(r'^(?:[A-Z][A-Z0-9_]*|%[-+.#0-9A-Za-z:*<> ]+|https?://\S+)$')

def literals(path):
    for no, line in enumerate(path.read_text(encoding='utf-8').splitlines(), 1):
        stripped=line.lstrip()
        if stripped.startswith(('//','/*','*','#include')): continue
        for match in STRING.finditer(line):
            try: value=ast.literal_eval(match.group())
            except (ValueError, SyntaxError): continue
            if ENGLISH.search(value) and not re.search(r'[А-Яа-яЁё]', value) and not TECHNICAL.fullmatch(value):
                yield no, value

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--update', action='store_true', help='accept current literals after review')
    args=ap.parse_args()
    allowpath=ROOT/'tools/l10n_allowlist.txt'
    found={(name, value) for name in FILES for _,value in literals(ROOT/name)}
    if args.update:
        allowpath.write_text('\n'.join(json.dumps([f,s], ensure_ascii=True) for f,s in sorted(found))+'\n', encoding='utf-8')
        return 0
    allowed=set()
    for line in allowpath.read_text(encoding='utf-8').splitlines():
        if line and not line.startswith('#'):
            allowed.add(tuple(json.loads(line)))
    new=found-allowed
    if new:
        for name,value in sorted(new):
            locations=[str(n) for n,v in literals(ROOT/name) if v==value]
            print(f'{name}:{",".join(locations)}: untranslated: {value!r}')
        print(f'Found {len(new)} new English user-visible literal(s).', file=sys.stderr)
        return 1
    print(f'Localization audit passed ({len(found)} reviewed technical/legacy entries).')
    return 0
if __name__ == '__main__': sys.exit(main())
