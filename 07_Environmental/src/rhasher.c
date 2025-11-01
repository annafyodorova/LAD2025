#include <rhash.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "config.h"

#ifdef READLINE
    #include <readline/readline.h>
#endif

int main(int argc, char *argv[]) {
    char *line = NULL;
    char buf[64];
    char result[130];

    rhash_library_init();

    while (true) {
        #ifdef READLINE
            line = (char *)readline(NULL);
            if (!line) {
                break;
            }
        #else
            int nread;
            size_t len;
            nread = getline(&line, &len, stdin);
            if (nread < 0) {
                break;
            }
        #endif

        char *algo = strtok(line, " ");
        if (!algo) {
            fprintf(stderr, "Cannot read command");
            free(line);
            continue;
        }

        char *file_or_string = strtok(NULL, " ");
        if (!file_or_string) {
            fprintf(stderr, "Cannot read filename/string.");
            free(line);
            continue;
        }

        line[strcspn(line, "\n")] = '\0';

        int hash_name;
        if (!strcasecmp(algo, "md5")) {
            hash_name = RHASH_MD5;
        } else if (!strcasecmp(algo, "sha1")) {
            hash_name = RHASH_SHA1;
        } else if (!strcasecmp(algo, "tth")) {
            hash_name = RHASH_TTH;
        } else {
            fprintf(stderr, "Bad algorithm name");
            free(line);
            continue;
        }

        // int hash_type = algo[0] == tolower(algo[0]) ? RHPR_BASE64 : RHPR_HEX;
        int use_base64 = (algo[0] >= 'a' && algo[0] <= 'z');
        int hash_type = use_base64 ? RHPR_BASE64 : RHPR_HEX;

        ssize_t err_code;
        if (file_or_string[0] != '"') {
            if (rhash_file(hash_name, file_or_string, buf) >= 0) {
                rhash_print_bytes(result, buf, rhash_get_digest_size(hash_name), hash_type);
                printf("%s\n", result);
                free(line);
                line = NULL;
            } else {
                fprintf(stderr, "Cannot hash string %s!\n", file_or_string);
                free(line);
                continue;
            }
        } else {
            size_t len = strlen(file_or_string);
            file_or_string[len - 1] = '\0';
            if (rhash_msg(hash_name, file_or_string + 1, strlen(file_or_string + 1), buf) >=0) {
                rhash_print_bytes(result, buf, rhash_get_digest_size(hash_name), hash_type);
                printf("%s\n", result);
                free(line);
                line = NULL;
            } else {
                fprintf(stderr, "Cannot hash file %s!\n", file_or_string);
                free(line);
                continue;
            }
        }
    }

    free(line);

    return 0;
}
