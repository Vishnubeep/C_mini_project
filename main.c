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
void modifyShape()
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

    Shape *s = &objects[index];

    switch(s->type)
    {
        case 1:
            printf("New x1 y1 x2 y2: ");
            scanf("%d%d%d%d",
                  &s->x1,&s->y1,
                  &s->x2,&s->y2);
            break;

        case 2:
            printf("New row col width height: ");
            scanf("%d%d%d%d",
                  &s->x1,&s->y1,
                  &s->width,&s->height);
            break;

        case 3:
            printf("New row col size: ");
            scanf("%d%d%d",
                  &s->x1,&s->y1,
                  &s->size);
            break;

        case 4:
            printf("New centerRow centerCol radius: ");
            scanf("%d%d%d",
                  &s->x1,&s->y1,
                  &s->radius);
            break;
    }

    redrawCanvas();
}

/* ---------- List Objects ---------- */

void listObjects()
{
    int i;

    printf("\nStored Objects\n");

    for(i = 0; i < objectCount; i++)
    {
        printf("%d -> ", i);

        if(objects[i].type == 1)
            printf("Line\n");
        else if(objects[i].type == 2)
            printf("Rectangle\n");
        else if(objects[i].type == 3)
            printf("Triangle\n");
        else if(objects[i].type == 4)
            printf("Circle\n");
    }
}

/* ---------- Main ---------- */

int main()
{
    int choice;

    clearCanvas();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Add Shape\n");
        printf("2. Delete Shape\n");
        printf("3. Modify Shape\n");
        printf("4. Display Canvas\n");
        printf("5. List Objects\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addShape();
                break;

            case 2:
                deleteShape();
                break;

            case 3:
                modifyShape();
                break;

            case 4:
                displayCanvas();
                break;

            case 5:
                listObjects();
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 0);

    return 0;
}
