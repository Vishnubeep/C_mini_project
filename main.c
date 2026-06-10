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
void drawRectangle(int x, int y, int width, int height)
{
    int i;

    for(i = 0; i < width; i++)
    {
        putPixel(x, y + i);
        putPixel(x + height - 1, y + i);
    }

    for(i = 0; i < height; i++)
    {
        putPixel(x + i, y);
        putPixel(x + i, y + width - 1);
    }
}

void drawTriangle(int x, int y, int size)
{
    drawLine(x, y, x + size, y - size);
    drawLine(x, y, x + size, y + size);
    drawLine(x + size, y - size, x + size, y + size);
}

void drawCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while(x <= y)
    {
        putPixel(xc + x, yc + y);
        putPixel(xc - x, yc + y);
        putPixel(xc + x, yc - y);
        putPixel(xc - x, yc - y);

        putPixel(xc + y, yc + x);
        putPixel(xc - y, yc + x);
        putPixel(xc + y, yc - x);
        putPixel(xc - y, yc - x);

        if(d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}
void redrawCanvas()
{
    int i;

    clearCanvas();

    for(i = 0; i < objectCount; i++)
    {
        switch(objects[i].type)
        {
            case 1:
                drawLine(
                    objects[i].x1,
                    objects[i].y1,
                    objects[i].x2,
                    objects[i].y2
                );
                break;

            case 2:
                drawRectangle(
                    objects[i].x1,
                    objects[i].y1,
                    objects[i].width,
                    objects[i].height
                );
                break;

            case 3:
                drawTriangle(
                    objects[i].x1,
                    objects[i].y1,
                    objects[i].size
                );
                break;

            case 4:
                drawCircle(
                    objects[i].x1,
                    objects[i].y1,
                    objects[i].radius
                );
                break;
        }
    }
}

/* ---------- Add Shape ---------- */

void addShape()
{
    Shape s;

    printf("\n1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Triangle\n");
    printf("4. Circle\n");

    printf("Enter shape type: ");
    scanf("%d", &s.type);

    switch(s.type)
    {
        case 1:
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d",
                  &s.x1,&s.y1,
                  &s.x2,&s.y2);
            break;

        case 2:
            printf("Enter top row and column: ");
            scanf("%d%d",&s.x1,&s.y1);

            printf("Enter width and height: ");
            scanf("%d%d",&s.width,&s.height);
            break;

        case 3:
            printf("Enter top point (row col): ");
            scanf("%d%d",&s.x1,&s.y1);

            printf("Enter size: ");
            scanf("%d",&s.size);
            break;

        case 4:
            printf("Enter center row and column: ");
            scanf("%d%d",&s.x1,&s.y1);

            printf("Enter radius: ");
            scanf("%d",&s.radius);
            break;

        default:
            printf("Invalid shape.\n");
            return;
    }

    objects[objectCount++] = s;

    redrawCanvas();
}
void deleteShape()
{
    int index;

    if(objectCount == 0)
    {
        printf("No objects available.\n");
        return;
    }

    printf("Enter object number (0 to %d): ",
           objectCount - 1);

    scanf("%d",&index);

    if(index < 0 || index >= objectCount)
    {
        printf("Invalid object.\n");
        return;
    }

    objects[index] = objects[objectCount - 1];
    objectCount--;

    redrawCanvas();
}

