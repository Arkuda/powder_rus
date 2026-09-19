#ifndef LOCALIZATION_H
#define LOCALIZATION_H

// Russian UI helpers.  Keys are deliberately separate from displayed text:
// save-game identifiers and enum names must never be translated.
const char *tr(const char *key);
const char *ru_plural(int value, const char *one, const char *few,
		      const char *many);

// Return the largest byte offset containing at most maxcolumns UTF-8 code
// points.  The offset is always on a code-point boundary.
int utf8_prefix(const char *text, int maxcolumns);
int utf8_columns(const char *text);

#endif
