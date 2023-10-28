#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define p printf
#define s scanf
#define g gotoxy

void drawOnScreen(x, y)
{
    g(x, y);
    p("%c", 219);
}

void drawVerticalLine(x, y, length)
{
    int i;
    for (i = 0; i < (length - (length / 2)); i++)
    {
        drawOnScreen(x, y + i);
    }
}

void drawHorizontalLine(x, y, length)
{

    int i;
    for (i = 0; i < length; i++)
    {
        drawOnScreen(x + i, y);
    }
}

/*
Returns center of cell,
location to which character can be placed
*/
int *drawCell(x, y, length)
{

    static int centerCoords[2];

    drawHorizontalLine(x, y, length);
    drawVerticalLine(x + length, y, length);
    drawVerticalLine(x, y, length);
    drawHorizontalLine(x, y + (length / 2), length + 1);

    centerCoords[0] = abs((x - length) / 2);
    centerCoords[1] = abs((y - length) / 2);

    return centerCoords;
}

/*
Returns all center coordinates of each cell
*/
int *drawGameboard(x, y, length)
{
    static int centerCoordinates[3][3];
    int i, j, k;

    for (i = 0; i < 3; i++)
    {
        int *centerCoords;
        centerCoords = drawCell(x + (length * i), y, length);
        centerCoordinates[0][i] = centerCoords;
    }

    for (i = 0; i < 3; i++)
    {
        int *centerCoords;
        drawCell(x + (length * i), y + ((length / 2)), length);
        centerCoordinates[1][i] = centerCoords;
    }

    for (i = 0; i < 3; i++)
    {
        int *centerCoords;
        drawCell(x + (length * i), y + ((length / 2) * 2), length);
        centerCoordinates[1][i] = centerCoords;
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            int *cellCenterCoords;
            cellCenterCoords = centerCoordinates[i][j];
            p("Expected to be 17: %i", cellCenterCoords[0]);
        }
    }

    return centerCoordinates;

    // drawCell(x, y, length);
    // drawCell(x + length, y, length);
}

int main()
{
    int i;
    int *center;
    char gameboard[3][3] = {
        {'n', 'n', 'n'},
        {'n', 'n', 'n'},
        {'n', 'n', 'n'}};

    clrscr();

    // centerCoords = drawGameboard(25, 5, 10);
    center = drawCell(10, 10, 5);

    g(40, 10);
    p("Expected to be 1: %i", center[0]);

    getch();
}