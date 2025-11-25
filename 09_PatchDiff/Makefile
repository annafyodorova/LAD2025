CFLAGS = -std=c99 -Wall -Wextra -O2
TARGETS = maze maze_1 maze_2 maze_3
SOURCES = maze.c maze_1.c maze_2.c maze_3.c

all: $(TARGETS)

maze_1.c: maze.c maze_1.patch
	patch -o $@ $< maze_1.patch

maze_2.c: maze_1.c maze_2.patch
	patch -o $@ $< maze_2.patch

maze_3.c: maze_2.c maze_3.patch
	patch -o $@ $< maze_3.patch

maze: maze.c
	gcc $(CFLAGS) -o $@ $<

maze_1: maze_1.c
	gcc $(CFLAGS) -o $@ $<

maze_2: maze_2.c
	gcc $(CFLAGS) -o $@ $<

maze_3: maze_3.c
	gcc $(CFLAGS) -o $@ $<

run: all
	./maze
	./maze_1 6
	./maze_2 .# 6
	./maze_3 12345 .# 6

clean:
	rm -f $(TARGETS) $(SOURCES:.c=.o) maze_1.c maze_2.c maze_3.c