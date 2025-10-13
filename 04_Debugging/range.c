#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n"
            "С одним параметром N — выводит в столбик последовательность [0, 1, … N-1]"
            "С двумя — M, N — последовательность [M, M+1, … N-1]"
            "С тремя — M, N, S — последовательность [M, M+S, M+2S, … N-1]");
        return 1;
    }

    long start, stop, step;

    if (argc == 2) {
        start = 0;
        stop = atol(argv[1]);
        step = 1;
    } else if (argc == 3) {
        start = atol(argv[1]);
        stop = atol(argv[2]);
        step = 1;
    } else if (argc == 4) {
        start = atol(argv[1]);
        stop = atol(argv[2]);
        step = atol(argv[3]);
        if (step == 0) {
            fprintf(stderr, "Error: step cannot be zero\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }

    long current = start;
    while (current < stop) {
            printf("%ld\n", current);
            current += step;
    }

    return 0;
}