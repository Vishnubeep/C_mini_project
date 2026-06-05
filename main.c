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
void putPixel(int x, int y)
{
    if(x >= 0 && x < ROWS && y >= 0 && y < COLS)
    {
        canvas[x][y] = '*';
    }
}

/* ---------- Drawing Functions ---------- */

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        putPixel(x1, y1);

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}