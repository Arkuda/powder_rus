#include "localization.h"
#include <string.h>

struct TRANSLATION { const char *key; const char *value; };

static const TRANSLATION translations[] = {
    { "menu.new_game", "Новая игра" },
    { "menu.continue", "Продолжить" },
    { "menu.options", "Настройки" },
    { "menu.help", "Помощь" },
    { "menu.quit", "Выход" },
    { "character.gender", "Пол?" },
    { "character.male", "Мужской" },
    { "character.female", "Женский" },
    { "character.name", "Имя?" },
    { "common.yes", "Да" },
    { "common.no", "Нет" },
    { "common.cancel", "Отмена" },
    { "inventory.title", "Инвентарь" },
    { "inventory.empty", "Инвентарь пуст." },
    { "death.title", "Вы погибли" },
    { "victory.title", "Победа!" },
    { 0, 0 }
};

const char *
tr(const char *key)
{
    for (int i = 0; translations[i].key; ++i)
	if (!strcmp(key, translations[i].key))
	    return translations[i].value;
    // A missing translation remains conspicuous without owning/copying memory.
    return key;
}

const char *
ru_plural(int value, const char *one, const char *few, const char *many)
{
    int n = value < 0 ? -value : value;
    if ((n % 100) >= 11 && (n % 100) <= 14)
	return many;
    if ((n % 10) == 1)
	return one;
    if ((n % 10) >= 2 && (n % 10) <= 4)
	return few;
    return many;
}

int
utf8_prefix(const char *text, int maxcolumns)
{
    int bytes = 0;
    int columns = 0;
    while (text[bytes] && columns < maxcolumns)
    {
	unsigned char c = (unsigned char) text[bytes];
	int width = 1;
	if ((c & 0xe0) == 0xc0) width = 2;
	else if ((c & 0xf0) == 0xe0) width = 3;
	else if ((c & 0xf8) == 0xf0) width = 4;
	// Invalid or truncated input is consumed byte-wise, never past NUL.
	for (int i = 1; i < width; ++i)
	    if (!text[bytes+i] || (((unsigned char) text[bytes+i] & 0xc0) != 0x80))
		width = 1;
	bytes += width;
	columns++;
    }
    return bytes;
}

int
utf8_columns(const char *text)
{
    int columns = 0;
    for (int pos = 0; text[pos]; ++columns)
	pos += utf8_prefix(text + pos, 1);
    return columns;
}
