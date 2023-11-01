#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define p printf
#define s scanf
#define g gotoxy

typedef struct
{
    int x;
    int y;
} Coords;

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
Coords drawCell(x, y, length)
{

    int centerX, centerY;
    Coords cellCenterCoords;
    drawHorizontalLine(x, y, length);
    drawVerticalLine(x + length, y, length);
    drawVerticalLine(x, y, length);
    drawHorizontalLine(x, y + (length / 2), length + 1);

    centerX = abs((x + (length / 2)));
    centerY = abs(y + (length * .33));

    cellCenterCoords.x = centerX;
    cellCenterCoords.y = centerY;
    return cellCenterCoords;
}

/*
Returns all center coordinates of each cell
*/
int *drawGameboard(x, y, length)
{
    static Coords collectiveCenterCoordinates[3][3];
    int i;

    for (i = 0; i < 3; i++)
    {
        Coords centerCoords;
        centerCoords = drawCell(x + (length * i), y, length);
        collectiveCenterCoordinates[0][i] = centerCoords;
        drawOnScreen(centerCoords.x, centerCoords.y);
    };

    for (i = 0; i < 3; i++)
    {
        Coords centerCoords;
        centerCoords = drawCell(x + (length * i), (y + (length / 2)), length);
        collectiveCenterCoordinates[0][i] = centerCoords;
        drawOnScreen(centerCoords.x, centerCoords.y);
    };

    for (i = 0; i < 3; i++)
    {
        Coords centerCoords;
        centerCoords = drawCell(x + (length * i), y + (length), length);
        collectiveCenterCoordinates[0][i] = centerCoords;
        drawOnScreen(centerCoords.x, centerCoords.y);
    };

    return *collectiveCenterCoordinates;

    // drawCell(x, y, length);
    // drawCell(x + length, y, length);
}

int main()
{
    int i;
    // int ***collectiveCenterCoordinates;
    char gameboard[3][3] = {
        {'n', 'n', 'n'},
        {'n', 'n', 'n'},
        {'n', 'n', 'n'}};

    int *collectiveCenterCoordinates;
    clrscr();
    // collectiveCenterCoordinates = drawCell(10, 10, 10);
    collectiveCenterCoordinates = drawGameboard(25, 5, 10);

    getch();

    return 0;
}