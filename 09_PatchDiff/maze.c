#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


const int DR[4] = {-1, 1, 0, 0};
const int DC[4] = {0, 0, -1, 1};
const int WALL_DR[4] = {-1, 1, 0, 0}; 
const int WALL_DC[4] = {0, 0, -1, 1};

void dfs(char** maze, bool** visited, int r, int c, int rooms) {
    visited[r][c] = true;
    int cell_r = 2 * r + 1;
    int cell_c = 2 * c + 1;

    int directions[4] = {0, 1, 2, 3};
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = directions[i];
        directions[i] = directions[j];
        directions[j] = tmp;
    }

    for (int i = 0; i < 4; i++) {
        int dir = directions[i];
        int nr = r + DR[dir];
        int nc = c + DC[dir];

        if (nr < 0 || nr >= rooms || nc < 0 || nc >= rooms)
            continue;
        if (visited[nr][nc])
            continue;

        int wall_r = cell_r + WALL_DR[dir];
        int wall_c = cell_c + WALL_DC[dir];
        maze[wall_r][wall_c] = '.';

        dfs(maze, visited, nr, nc, rooms);
    }
}

int main(int argc, char *argv[]) {
    srand((unsigned)time(NULL));

    int rooms = 6;
    int maze_size = 2*rooms + 1;

    char **maze = malloc(maze_size * sizeof(char*));
    for (int i = 0; i < maze_size; i++) {
        maze[i] = malloc((maze_size + 1) * sizeof(char));
        for (int j = 0; j < maze_size; j++) {
            maze[i][j] = (i % 2 == 1 && j % 2 == 1) ? '.' : '#';
        }
        maze[i][maze_size] = '\0';
    }

    bool **visited = malloc(rooms * sizeof(bool*));
    for (int i = 0; i < rooms; i++) {
        visited[i] = calloc(rooms, sizeof(bool));
    }

    dfs(maze, visited, 0, 0, rooms);

    for (int i = 0; i < maze_size; i++) {
        puts(maze[i]);
    }

    for (int i = 0; i < maze_size; i++) {
        free(maze[i]);
    }
    free(maze);

    for (int i = 0; i < rooms; i++) {
        free(visited[i]);
    }
    free(visited);

    return 0;
}