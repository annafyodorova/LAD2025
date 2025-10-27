#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

typedef int (*remove_type)(const char *);

int remove(const char *filename) {
    int err_code = 0;
    if (!strstr(filename, "PROTECT")) {
        err_code = ((remove_type)(dlsym(RTLD_NEXT, "remove")))(filename);
    }
    return err_code;
}