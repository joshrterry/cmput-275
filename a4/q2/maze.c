#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "maze.h"

struct Maze {
    char **grid;
    int rows, cols;
    struct Pos start;
    struct Pos player;
};

struct Maze *readMaze() {
    struct Maze *maze = malloc(sizeof(struct Maze));
    if (!maze) return NULL;
    
    maze->grid = NULL;
    maze->rows = 0;
    maze->cols = 0;
    char line[1024];
    int start_count = 0, goal_count = 0;
    
    while (fgets(line, sizeof(line), stdin) && line[0] != '\n') {
        int len = strlen(line);
        if (line[len - 1] == '\n') line[len - 1] = '\0';
        
        maze->grid = realloc(maze->grid, (maze->rows + 1) * sizeof(char *));
        maze->grid[maze->rows] = strdup(line);
        
        if (maze->cols < len - 1) {
            maze->cols = len - 1;
        }
        
        for (int col = 0; col < len - 1; col++) {
            if (line[col] == 'S') {
                maze->start = (struct Pos){col, maze->rows};
                start_count++;
            } else if (line[col] == 'G') {
                goal_count++;
            }
        }
        maze->rows++;
    }
    
    if (start_count != 1 || goal_count < 1) {
        for (int i = 0; i < maze->rows; i++) free(maze->grid[i]);
        free(maze->grid);
        free(maze);
        return NULL;
    }
    
    maze->player = maze->start;
    return maze;
}

struct Pos makeMove(struct Maze *maze, char direction) {
    int dx = 0, dy = 0;
    if (direction == 'n') dy = -1;
    else if (direction == 's') dy = 1;
    else if (direction == 'e') dx = 1;
    else if (direction == 'w') dx = -1;
    
    int nx = maze->player.x + dx;
    int ny = maze->player.y + dy;
    
    while (nx >= 0 && ny >= 0 && ny < maze->rows && nx < maze->cols && maze->grid[ny][nx] != 'X') {
        maze->player.x = nx;
        maze->player.y = ny;
        
        if (maze->grid[ny][nx] == 'G') {
            return (struct Pos){-1, -1};
        }
        
        if (maze->grid[ny][nx] >= '0' && maze->grid[ny][nx] <= '9') {
            char teleport = maze->grid[ny][nx];
            for (int r = 0; r < maze->rows; r++) {
                for (int c = 0; c < maze->cols; c++) {
                    if (maze->grid[r][c] == teleport && (r != ny || c != nx)) {
                        nx = c;
                        ny = r;
                        maze->player.x = nx;
                        maze->player.y = ny;
                        break;
                    }
                }
            }
        }
        
        if (maze->grid[ny][nx] != 'I') {
            break;
        }
        
        nx += dx;
        ny += dy;
    }
    
    return maze->player;
}

void reset(struct Maze *maze) {
    maze->player = maze->start;
}

void printMaze(struct Maze *maze) {
    for (int i = 0; i < maze->cols + 2; i++) printf("-");
    printf("\n");
    
    for (int y = 0; y < maze->rows; y++) {
        printf("|");
        for (int x = 0; x < maze->cols; x++) {
            if (maze->player.x == x && maze->player.y == y) printf("P");
            else printf("%c", maze->grid[y][x]);
        }
        printf("|\n");
    }
    
    for (int i = 0; i < maze->cols + 2; i++) printf("-");
    printf("\n");
}

struct Maze *destroyMaze(struct Maze *maze) {
    for (int i = 0; i < maze->rows; i++) free(maze->grid[i]);
    free(maze->grid);
    free(maze);
    return NULL;
}
