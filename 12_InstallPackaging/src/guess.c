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

#define _(STRING) gettext(STRING)

/**
 * @brief Enable roman numerals mode
 */
static int use_roman = 0;

/**
 * @brief Roman numerals lookup table for numbers 1..100
 */
static const char *roman_table[101] = {
    [1] = "I",     [2] = "II",    [3] = "III",   [4] = "IV",    [5] = "V",
    [6] = "VI",    [7] = "VII",   [8] = "VIII",  [9] = "IX",   [10] = "X",
    [11] = "XI",   [12] = "XII",  [13] = "XIII", [14] = "XIV", [15] = "XV",
    [16] = "XVI",  [17] = "XVII", [18] = "XVIII",[19] = "XIX", [20] = "XX",
    [30] = "XXX",  [40] = "XL",   [50] = "L",    [60] = "LX",
    [70] = "LXX",  [80] = "LXXX", [90] = "XC",   [100] = "C"
};

/**
 * @brief Convert arabic number to roman numeral
 * @param value Number from 1 to 100
 * @return Roman numeral string or NULL
 */
static const char *arabic_to_roman(int value) {
    if (value < 1 || value > 100)
        return NULL;

    if (roman_table[value])
        return roman_table[value];

    static char buf[16];
    int tens = (value / 10) * 10;
    int ones = value % 10;

    snprintf(buf, sizeof(buf), "%s%s",
             roman_table[tens],
             roman_table[ones]);
    return buf;
}

/**
 * @brief Convert roman numeral to arabic number
 * @param roman Roman numeral string
 * @return Number from 1 to 100 or -1 on error
 */
static int roman_to_arabic(const char *roman) {
    for (int i = 1; i <= 100; i++) {
        const char *r = arabic_to_roman(i);
        if (r && strcmp(r, roman) == 0)
            return i;
    }
    return -1;
}

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
