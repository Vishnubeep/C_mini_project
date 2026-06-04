#include <stdio.h>
#include <stdlib.h>

#define ROWS 30
#define COLS 60
#define MAX_OBJECTS 100

char canvas[ROWS][COLS];

typedef struct
{
    int type;

    int x1, y1;
    int x2, y2;

    int width;
    int height;

    int size;
    int radius;

} Shape;

Shape objects[MAX_OBJECTS];
int objectCount = 0;

void clearCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    int i, j;

    printf("\n");

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}
