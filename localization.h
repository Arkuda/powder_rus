#ifndef __localization_h__
#define __localization_h__

enum L10N_KEY
{
    L10N_YES,
    L10N_NO,
    L10N_TOTAL
};

void l10n_init();
const char *l10n_get(L10N_KEY key);

#endif
