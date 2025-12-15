/**
 * @file guess.c
 * @brief Number guessing game with roman numeral support
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include "config.h"
#include "libroman.h"

#define _(STRING) gettext(STRING)

/**
 * @brief Enable roman numerals mode
 */
static int use_roman = 0;
 
















































/**
 * @brief Print help message
 */
static void print_help(void) {
    printf(
        _("Usage: guess [OPTIONS]\n\n"
          "Options:\n"
          "  -r        Use roman numerals (I, V, X)\n"
          "  --help    Show this help and exit\n"
          "  --help-md Show help in Markdown format\n\n"
          "Описание:\n"
          "  Программа угадывает число от 1 до 100.\n"
          "  В режиме -r используются римские цифры.\n")
    );
}

/**
 * @brief Print help in Markdown format
 */
static void print_help_md(void) {
    printf(
        "# Guess — Number guessing game\n\n"
        "## Usage\n"
        "`guess [OPTIONS]`\n\n"
        "## Options\n"
        "- `-r` — Roman numerals mode\n"
        "- `--help` — Show help\n"
    );
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    /* Parse command-line arguments */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            use_roman = 1;
        } else if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "--help-md") == 0) {
            print_help_md();
            return 0;
        }
    }

    printf(_("Think of a number from 1 to 100: \n"));

    char responce[256];
    int start = 1, end = 100, mid;

    while (start < end) {
        mid = (start + end) / 2;

        if (use_roman) {
            printf(_("Is your number bigger than %s? (%s/%s): "),
                   arabic_to_roman(mid), _("yes"), _("no"));
        } else {
            printf(_("Is your number bigger than %d? (%s/%s): "),
                   mid, _("yes"), _("no"));
        }

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
            fprintf(stderr,
                    _("Invalid input error. Enter '%s' or '%s'.\n"),
                    _("yes"), _("no"));
            continue;
        }
    }

    if (use_roman) {
        printf(_("Your number is %s\n"), arabic_to_roman(start));
    } else {
        printf(_("Your number is %d\n"), start);
    }

    return 0;
}
