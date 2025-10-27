#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define EXIT_INVALID_ARGS 1
#define EXIT_OPEN_FAIL 2
#define EXIT_CLOSE_FAIL 3
#define EXIT_ALLOC_FAIL 4
#define EXIT_READ_FAIL 5
#define EXIT_WRITE_FAIL 7
#define EXIT_REMOVE_FAIL 8
#define BUF_SIZE 1024

void remove_file(const char *filename) {
    int err_code = remove(filename);
    if (err_code < 0) {
        perror("error remove file");
        exit(EXIT_REMOVE_FAIL);
    }
}

void close_file(int fd) {
    int err_code = close(fd);
    if (err_code < 0) {
        perror("error close file");
        exit(EXIT_CLOSE_FAIL);
    }
}

int open_file(const char *filename, int flags, mode_t mode) {
    int fd = open(filename, flags, mode);
    if (fd < 0) {
        perror("error open file");
        exit(EXIT_OPEN_FAIL);
    }
    return fd;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        exit(EXIT_INVALID_ARGS);
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];

    int fd_in = open_file(infile, O_RDONLY, 0);

    char buffer[BUF_SIZE];

    int fd_out = open_file(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);

    ssize_t nread = 1, nwrite;
    while (nread > 0) {
        nread = read(fd_in, buffer, sizeof(buffer));
        if (nread < 0) {
            perror("error read file");
            close_file(fd_in);
            close_file(fd_out);
            remove_file(outfile);
            exit(EXIT_READ_FAIL);
        }
        nwrite = write(fd_out, buffer, nread);
        if (nwrite < nread) {
            perror("error write file");
            close_file(fd_in);
            close_file(fd_out);
            remove_file(outfile);
            exit(EXIT_WRITE_FAIL);
        }
    }

    close_file(fd_in);
    close_file(fd_out);

    remove_file(infile);

    return 0;
}