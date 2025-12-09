#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include "config.h"

#define _(STRING) gettext(STRING)

int main(int argc, char **argv) {
	setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
    printf(_("Think of a number from 1 to 100: \n"));

    char responce[256];
    int start = 1, end = 100, mid;

    while (start < end) {
        mid = (start + end) / 2;
        printf(_("Is your number bigger than %d? (%s/%s): "), mid, _("yes"), _("no"));
        fflush(stdout);

        if (scanf("%255s", responce) != 1) {
            fprintf(stderr, _("Read error\n"));
            return 1;
        }

        if (strcmp(responce, _("yes")) == 0) {
            start = mid + 1;
        } else if (strcmp(responce, _("no")) == 0) {
            end = mid;
        } else {
            fprintf(stderr, _("Invalid input error. Enter '%s' or '%s'.\n"), _("yes"), _("no"));
            continue;
        }
    }

    printf(_("Your number is %d\n"), start);
    return 0;
}