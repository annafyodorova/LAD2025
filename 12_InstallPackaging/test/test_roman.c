#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../src/roman.h"

static void test_arabic_to_roman(void) {
    assert(strcmp(arabic_to_roman(1), "I") == 0);
    assert(strcmp(arabic_to_roman(4), "IV") == 0);
    assert(strcmp(arabic_to_roman(9), "IX") == 0);
    assert(strcmp(arabic_to_roman(42), "XLII") == 0);
    assert(strcmp(arabic_to_roman(100), "C") == 0);
}

static void test_roman_to_arabic(void) {
    assert(roman_to_arabic("I") == 1);
    assert(roman_to_arabic("IV") == 4);
    assert(roman_to_arabic("IX") == 9);
    assert(roman_to_arabic("XLII") == 42);
    assert(roman_to_arabic("C") == 100);
    assert(roman_to_arabic("INVALID") == -1);
}

int main(void) {
    test_arabic_to_roman();
    test_roman_to_arabic();

    printf("All roman tests passed\n");
    return 0;
}
