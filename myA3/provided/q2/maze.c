#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "maze.h"

struct Maze {
    char **maze;
    int rows;
    int cols;
    int xStart;
    int yStart;
    int xPlayer;
    int yPlayer;
};

static void freeRows(char **rows, int count) {
    for (int i = 0; i < count; i++) {
        free(rows[i]);
    }
    free(rows);
}

static int inBounds(struct Maze *m, int x, int y) {
    return x >= 0 && x < m->cols && y >= 0 && y < m->rows;
}

static int isTeleporter(char c) {
    return c >= '0' && c <= '9';
}

static void teleport(struct Maze *m, int *x, int *y) {
    char location = m->maze[*y][*x];

    for (int a = 0; a < m->rows; a++) {
        for (int b = 0; b < m->cols; b++) {
            if (a == *y && b == *x) {
                continue;
            } else if (m->maze[a][b] == location) {
                *x = b;
                *y = a;
                return;
            }
        }
    }
}

struct Maze *readMaze(){
    char currentRow[1024];
    char **rows = NULL;
    int startCount = 0;
    int goalCount = 0;
    int rowCount = 0;
    int cols = 0;
    int xStart = 0;
    int yStart = 0;

    while (fgets(currentRow, sizeof(currentRow), stdin) != NULL){
        int len = (int)strlen(currentRow);
        char **newRows;
        char *temp;

        if (len > 0 && currentRow[len - 1] == '\n'){
            currentRow[len - 1] = '\0';
            len--;
        } 
        if (len == 0){
            break;
        }

        if (cols == 0){
            cols = len;
        } else if (cols != len){
            freeRows(rows, rowCount);
            return NULL;
        }

        temp = malloc((size_t)len + 1);
        if (temp == NULL){
            freeRows(rows, rowCount);
            return NULL;
        }
        strcpy(temp, currentRow);

        for (int j = 0; j < len; j++){
            if (temp[j] == 'S') {
                startCount++;
                xStart = j;
                yStart = rowCount;
            } else if (temp[j] == 'G'){
                goalCount++;
            }
        }
        newRows = realloc(rows, sizeof(char *) * (size_t)(rowCount + 1));
        if (newRows == NULL){
            free(temp);
            freeRows(rows, rowCount);
            return NULL;
        }

        rows = newRows;
        rows[rowCount] = temp;
        rowCount++;
    }

    if (startCount != 1 || goalCount < 1 || rowCount == 0){
        freeRows(rows, rowCount);
        return NULL;
    }
    {
        struct Maze *m = malloc(sizeof(struct Maze));
        if (m == NULL){
            freeRows(rows, rowCount);
            return NULL;
        }

        m->maze = rows;
        m->rows = rowCount;
        m->cols = cols;
        m->xStart = xStart;
        m->yStart = yStart;
        m->xPlayer = m->xStart;
        m->yPlayer = m->yStart;

        return m;
    }
}

void printMaze(struct Maze *m) {
    assert(m != NULL);

    for (int i = 0; i < m->cols + 2; i++) {
        printf("=");
    }
    printf("\n");

    for (int i = 0; i < m->rows; i++) {
        printf("|");
        for (int j = 0; j < m->cols; j++) {
            if (i == m->yPlayer && j == m->xPlayer) {
                printf("P");
            } else {
                printf("%c", m->maze[i][j]);
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < m->cols + 2; i++) {
        printf("=");
    }
    printf("\n");
}

void reset(struct Maze *m) {
    assert(m != NULL);
    m->xPlayer = m->xStart;
    m->yPlayer = m->yStart;
}

struct Pos makeMove(struct Maze *m, char dir) {
    struct Pos p;
    int xDir = 0;
    int yDir = 0;
    int xNext, yNext;

    assert(m != NULL);

    if (dir == 'n') {
        yDir = -1;
    } else if (dir == 'e') {
        xDir = 1;
    } else if (dir == 's') {
        yDir = 1;
    } else if (dir == 'w') {
        xDir = -1;
    }

    xNext = m->xPlayer + xDir;
    yNext = m->yPlayer + yDir;

    if (!inBounds(m, xNext, yNext) || m->maze[yNext][xNext] == 'X') {
        p.x = m->xPlayer;
        p.y = m->yPlayer;
        return p;
    }

    m->xPlayer = xNext;
    m->yPlayer = yNext;

    while (1) {
        char tile = m->maze[m->yPlayer][m->xPlayer];

        if (tile == 'G') {
            p.x = -1;
            p.y = -1;
            return p;
        }

        if (isTeleporter(tile)) {
            teleport(m, &m->xPlayer, &m->yPlayer);
            tile = m->maze[m->yPlayer][m->xPlayer];

            if (tile == 'G') {
                 p.x = -1;
                p.y = -1;
                return p;
            }
        }

        if (tile == 'I') {
            xNext = m->xPlayer + xDir;
            yNext = m->yPlayer + yDir;

            if (!inBounds(m, xNext, yNext) || m->maze[yNext][xNext] == 'X') {
                break;
            }

            m->xPlayer = xNext;
            m->yPlayer = yNext;
            continue;
        }

        break;
    }

    if (m->maze[m->yPlayer][m->xPlayer] == 'G') {
        p.x = -1;
        p.y = -1;
    } else {
        p.x = m->xPlayer;
        p.y = m->yPlayer;
    }
    return p;
}

struct Maze *destroyMaze(struct Maze *m) {
    if (m == NULL) {
        return NULL;
    }

    freeRows(m->maze, m->rows);
    free(m);
    return NULL;
}
