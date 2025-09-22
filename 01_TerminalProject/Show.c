#include <ncurses.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <fcntl.h>

#define DX 5

int main(int argc, char *argv[]) {
    struct stat info;
    stat(argv[1], &info);
    size_t len = info.st_size;

    char *buffer = malloc(len + 2);

    int fd = open(argv[1], O_RDONLY);

    ssize_t total_read = 0;
    while (total_read < len) {
        ssize_t r = read(fd, buffer + total_read, len - total_read);
        if (r <= 0) break;
        total_read += r;
    }
    close(fd);
    len = total_read;

    buffer[len] = '\n'; 
    if (buffer[len - 1] != '\n') {
        buffer[len] = '\n';
    }

    int line_count = 0;
    char *ptr = buffer;
    while ((ptr = strchr(ptr, '\n')) != NULL) {
        line_count++;
        ptr++;
    }

    char **strings = calloc(line_count + 1, sizeof(char*));

    ptr = buffer;
    for (int i = 0; i < line_count; i++) {
        strings[i] = ptr;
        ptr = strchr(ptr, '\n');
        if (ptr) {
            *ptr = '\0'; 
            ptr++;
        }
    }

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();

    WINDOW *win = newwin(LINES - 2*DX - 2, COLS - 2*DX - 2, DX+1, DX+1);

    keypad(win, TRUE);

    int visible_lines = LINES - 2*DX - 4;
    int start_line = 0;
    int ch;

    do {
        werase(win);
        box(win, 0, 0);
        mvwprintw(win, 0, 1, " %s ", argv[1]);

        for (int i = 0; i < visible_lines && start_line + i < line_count; i++) {
            mvwprintw(win, 1 + i, 1, "%.*s", COLS - 2*DX - 4, strings[start_line + i]);        
        }

        wrefresh(win);

        ch = wgetch(win);
        if (ch == ' ' && start_line + visible_lines < line_count) {
            start_line++;
        }
    } while (ch != 27); 

    delwin(win);
    endwin();

    free(strings);
    free(buffer);

    return 0;
}