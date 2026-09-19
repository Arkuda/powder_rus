#include "../localization.h"

#include <string.h>
int main() {
 if (!(!strcmp(ru_plural(1,"ход","хода","ходов"),"ход"))) return 1;
 if (!(!strcmp(ru_plural(2,"ход","хода","ходов"),"хода"))) return 1;
 if (!(!strcmp(ru_plural(5,"ход","хода","ходов"),"ходов"))) return 1;
 if (!(!strcmp(ru_plural(11,"ход","хода","ходов"),"ходов"))) return 1;
 if (!(!strcmp(ru_plural(21,"ход","хода","ходов"),"ход"))) return 1;
 const char *s="абвг";
 if (!(utf8_columns(s)==4)) return 1;
 if (!(utf8_prefix(s,3)==6)) return 1;
 if (!(!strcmp(tr("menu.help"),"Помощь"))) return 1;
}
