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

void drawBlockOnScreen(x, y)
{
    g(x, y);
    p("%c", 219);
}

void drawOnScreen(character, x, y)
{
    g(x, y);
    p("%c", character);
}

void drawVerticalLine(x, y, length)
{
    int i;
    for (i = 0; i < (length - (length / 2)); i++)
    {
        drawBlockOnScreen(x, y + i);
    }
}

void drawHorizontalLine(x, y, length)
{

    int i;
    for (i = 0; i < length; i++)
    {
        drawBlockOnScreen(x + i, y);
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
void drawGameboard(int x, int y, int length, char gameboard[3][3])
{
    int i;

    for (i = 0; i < 3; i++)
    {
        Coords centerCoords;
        centerCoords = drawCell(x + (length * i), y, length);
        drawOnScreen(gameboard[0][i], centerCoords.x, centerCoords.y);
    };

    for (i = 0; i < 3; i++)
    {
        Coords centerCoords;
        centerCoords = drawCell(x + (length * i), (y + (length / 2)), length);
        drawOnScreen(gameboard[1][i], centerCoords.x, centerCoords.y);
    };

    for (i = 0; i < 3; i++)
    {
        Coords centerCoords;
        centerCoords = drawCell(x + (length * i), y + (length), length);
        drawOnScreen(gameboard[2][i], centerCoords.x, centerCoords.y);
    };

    // drawCell(x, y, length);
    // drawCell(x + length, y, length);
}

int main()
{
    int i, j;
    // int ***collectiveCenterCoordinates;
    char gameboard[3][3] = {
        {'n', 'n', 'n'},
        {'n', 'n', 'n'},
        {'n', 'n', 'n'}};

    clrscr();
    // collectiveCenterCoordinates = drawCell(10, 10, 10);
    drawGameboard(25, 5, 10, gameboard);

    getch();

    return 0;
}