#include <stdio.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MATCHES 10
#define BUFSIZE 8192

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <regexp> <substitution> <string>\n", argv[0]);
        return 1;
    }

    char *regexp = argv[1];
    char *substitution = argv[2];
    char *input = argv[3];

    regex_t reg;
    int ret = regcomp(&reg, regexp, REG_EXTENDED);
    if (ret != 0) {
        char errbuf[100];
        regerror(ret, &reg, errbuf, 100);
        printf("%s\n", errbuf);
        regfree(&reg);
        return 1;
    }

    regmatch_t matches[MAX_MATCHES];
    ret = regexec(&reg, input, MAX_MATCHES, matches, 0);
    if (ret == REG_NOMATCH) {
        printf("No matches\n");
        regfree(&reg);
        return 0;
    } else if (ret != 0) { 
        char errbuf[100];
        regerror(ret, &reg, errbuf, 100);
        printf("%s\n", errbuf);       
        regfree(&reg);
        return 1;
    }

    char result[BUFSIZE];
    char *out = result;
    const char *end = result + sizeof(result) - 1;

    int prefix_len = matches[0].rm_so;
    if (prefix_len > 0) {
        memcpy(out, input, prefix_len);
        out += prefix_len;
    }

    const char *next = substitution;

    while (*next && out < end) {
        if (*next == '\\') {
            next++;
            if (*next == '\\') {
                *out++ = '\\';
                next++;
            } else if (*next >= '0' && *next <= '9') {
                int ref = *next - '0';
                regmatch_t m = matches[ref];
                if (m.rm_so != -1) {
                    int len = m.rm_eo - m.rm_so;
                    memcpy(out, input + m.rm_so, len);
                    out += len;
                }
                next++;
            } else {
                *out++ = '\\';
                if (*next) *out++ = *next++;
            }
        } else {
            *out++ = *next++;
        }
    }

    int start = matches[0].rm_eo;
    int len = strlen(input) - start;
    if (len > 0) {
        memcpy(out, input + start, len);
        out += len;
    }

    *out = '\0';

    puts(result);

    regfree(&reg);

    return 0;

}