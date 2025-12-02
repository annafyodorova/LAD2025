
test_buf.c: $(srcdir)/tests.ts
	sed -e '/^#test /{s/^#test \(.*\)/START_TEST(\1)\n{/;b;}' \
	    -e 's/^}/}\nEND_TEST\n/' \
	    -e '1i
#include "../src/buf.h"
#include <check.h>
#include <stdlib.h>' \
	    -e '$$a\
Suite *buf_suite(void) { \
    Suite *s = suite_create("buf"); \
    TCase *tc = tcase_create("Core"); \
    tcase_add_test(tc, benchtest); \
    tcase_add_test(tc, initialization_and_buf_free); \
    tcase_add_test(tc, clear_null_ptr); \
    tcase_add_test(tc, buf_push_and_index_operator); \
    tcase_add_test(tc, buf_grow_buf_trunc); \
    tcase_add_test(tc, buf_pop); \
    suite_add_tcase(s, tc); \
    return s; \
} \
int main(void) { \
    Suite *s = buf_suite(); \
    SRunner *sr = srunner_create(s); \
    srunner_run_all(sr, CK_NORMAL); \
    int nf = srunner_ntests_failed(sr); \
    srunner_free(sr); \
    return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE; \
}' $< > $@.tmp && mv $@.tmp $@