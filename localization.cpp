#include "localization.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *glb_l10n_en[L10N_TOTAL] =
{
    "Yes",
    "No",
};

static const char *glb_l10n_cur[L10N_TOTAL] =
{
    "Yes",
    "No",
};

static bool glb_l10n_inited = false;

static bool
l10n_is_ru_selected()
{
    const char *lang = getenv("POWDER_LANG");
    if (!lang)
        lang = getenv("LANG");
    if (!lang)
        return false;

    return !strncmp(lang, "ru", 2) || !strncmp(lang, "RU", 2);
}

void
l10n_init()
{
    int i;
    FILE *fp;
    char line[256];

    if (glb_l10n_inited)
        return;
    glb_l10n_inited = true;

    for (i = 0; i < L10N_TOTAL; i++)
        glb_l10n_cur[i] = glb_l10n_en[i];

    if (!l10n_is_ru_selected())
        return;

    fp = fopen("lang/ru/messages.txt", "r");
    if (!fp)
        return;

    while (fgets(line, sizeof(line), fp))
    {
        char *eq = strchr(line, '=');
        char *value;
        if (!eq)
            continue;

        *eq = '\0';
        value = eq + 1;

        char *nl = strpbrk(value, "\r\n");
        if (nl)
            *nl = '\0';

        if (!strcmp(line, "YES"))
            glb_l10n_cur[L10N_YES] = strdup(value);
        else if (!strcmp(line, "NO"))
            glb_l10n_cur[L10N_NO] = strdup(value);
    }

    fclose(fp);
}

const char *
l10n_get(L10N_KEY key)
{
    l10n_init();
    return glb_l10n_cur[key];
}
