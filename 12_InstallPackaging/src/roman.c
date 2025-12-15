
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
const char *arabic_to_roman(int value) {
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
int roman_to_arabic(const char *roman) {
    for (int i = 1; i <= 100; i++) {
        const char *r = arabic_to_roman(i);
        if (r && strcmp(r, roman) == 0)
            return i;
    }
    return -1;
}
