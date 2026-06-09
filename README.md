# 2D Graphics Editor in C

## Overview

This project is a simple menu-driven 2D Graphics Editor developed in C. The editor uses a 2D character array as a drawing canvas. The canvas is initially filled with the underscore (_) character and graphical objects are drawn using the asterisk (*) character.

The program allows users to create, modify, delete and display different graphical objects directly from the terminal.

## Features

* Draw a Line
* Draw a Rectangle
* Draw a Triangle
* Draw a Circle
* Add new objects to the canvas
* Delete existing objects
* Modify object properties
* Display the current picture
* Store multiple objects using structures

## Technologies Used

* C Programming Language
* Standard C Libraries

  * stdio.h
  * stdlib.h

## Data Structures Used

### 1. 2D Character Array

The drawing canvas is represented using a 2D character array.

```c
char canvas[ROWS][COLS];
```

### 2. Structure

A structure is used to store information about graphical objects.

```c
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
```

## Menu Options

1. Add Shape
2. Delete Shape
3. Modify Shape
4. Display Canvas
5. List Objects
6. Exit

## Shape Types

### Line

Defined using two end points.

### Rectangle

Defined using top-left position, width and height.

### Triangle

Defined using a top point and size.

### Circle

Defined using center coordinates and radius.

## How the Program Works

1. The canvas is initialized with '_' characters.
2. Whenever a shape is added, deleted or modified, the canvas is cleared.
3. All stored objects are redrawn on the canvas.
4. The updated canvas is displayed whenever requested.

## Compilation

Using GCC:

```bash
gcc graphics_editor.c -o graphics_editor
```

## Execution

Linux / Mac:

```bash
./graphics_editor
```

Windows:

```bash
graphics_editor.exe
```

## Sample Output

```text
===== 2D GRAPHICS EDITOR =====
1. Add Shape
2. Delete Shape
3. Modify Shape
4. Display Canvas
5. List Objects
0. Exit
```

## Learning Outcomes

* Working with 2D arrays
* Using structures in C
* Menu-driven programming
* Implementing basic graphics algorithms
* Managing multiple objects using arrays

## Author

Vishnu Haridasan

## Course

Programming for Problem Solving / C Programming Laboratory
