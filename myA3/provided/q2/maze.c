#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Maze {
    char **maze;
    int rows;
    int cols;
    int xStart;
    int yStart;
    int xPlayer;
    int yPlayer;
};