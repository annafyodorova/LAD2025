#include "../src/buf.h"
#include <check.h>

#test push_pop
    int *v = NULL;
    for (int i = 0; i < 100; i++) {
        buf_push(v, i);
        ck_assert_uint_eq(buf_size(v), (size_t)(i + 1));
    }
    for (int i = 99; i >= 0; i--) {
        int val = buf_pop(v);
        ck_assert_int_eq(val, i);
    }
    ck_assert_uint_eq(buf_size(v), 0);
    buf_free(v);
    ck_assert_ptr_null(v);

#test grow_capacity
    double *v = NULL;
    ck_assert_uint_eq(buf_size(v), 0);
    ck_assert_uint_eq(buf_capacity(v), 0);

    buf_grow(v, 50);
    ck_assert_uint_eq(buf_capacity(v), 50);
    ck_assert_uint_eq(buf_size(v), 0);

    for (size_t i = 0; i < 50; i++) {
        buf_push(v, (double)i);
    }
    ck_assert_uint_eq(buf_size(v), 50);
    ck_assert_uint_eq(buf_capacity(v), 50);

    buf_free(v);

#test trunc
    char *v = NULL;
    for (int i = 0; i < 20; i++) {
        buf_push(v, (char)('A' + i));
    }
    ck_assert_uint_eq(buf_size(v), 20);
    ck_assert_uint_ge(buf_capacity(v), 20);

    buf_trunc(v, 10);
    ck_assert_uint_eq(buf_capacity(v), 10);
    ck_assert_uint_eq(buf_size(v), 10); // size clamped

    buf_trunc(v, 0);
    ck_assert_ptr_null(v);

#test clear
    float *v = NULL;
    for (size_t i = 0; i < 5; i++) {
        buf_push(v, (float)i);
    }
    ck_assert_uint_eq(buf_size(v), 5);
    buf_clear(v);
    ck_assert_uint_eq(buf_size(v), 0);
    ck_assert_uint_ge(buf_capacity(v), 5); // capacity unchanged
    buf_free(v);

#test struct
    struct point { int x, y; };
    struct point *v = NULL;

    buf_push(v, ((struct point){10, 20}));
    buf_push(v, ((struct point){30, 40}));

    ck_assert_uint_eq(buf_size(v), 2);
    ck_assert_int_eq(v[0].x, 10);
    ck_assert_int_eq(v[0].y, 20);
    ck_assert_int_eq(v[1].x, 30);
    ck_assert_int_eq(v[1].y, 40);

    struct point p = buf_pop(v);
    ck_assert_int_eq(p.x, 30);
    ck_assert_int_eq(p.y, 40);
    ck_assert_uint_eq(buf_size(v), 1);

    buf_free(v);

#test init_capacity
    short *v = NULL;
    buf_push(v, 42);
    ck_assert_uint_eq(buf_capacity(v), 8); // BUF_INIT_CAPACITY
    ck_assert_uint_eq(buf_size(v), 1);
    buf_free(v);

#test clear_null_ptr
    float *v = NULL;
    ck_assert_uint_eq(buf_size(v), 0);
    ck_assert_ptr_null(v);
    buf_clear(v); // should be safe
    ck_assert_uint_eq(buf_size(v), 0);