#ifndef ROMAN_H
#define ROMAN_H

/**
 * @brief Convert arabic number to roman numeral
 * @param value Number from 1 to 100
 * @return Roman numeral string or NULL
 */
const char *arabic_to_roman(int value);

/**
 * @brief Convert roman numeral to arabic number
 * @param roman Roman numeral string
 * @return Number from 1 to 100 or -1 on error
 */
int roman_to_arabic(const char *roman);

#endif
