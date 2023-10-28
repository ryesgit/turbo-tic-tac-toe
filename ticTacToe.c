#include <stdio.h>
#include <conio.h>

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

void drawCell(x, y, length)
{
    drawHorizontalLine(x, y, length);
    drawVerticalLine(x + length, y, length);
    drawVerticalLine(x, y, length);
    drawHorizontalLine(x, y + (length / 2), length + 1);
}

void drawGameboard(x, y, length)
{

    int i;

    for (i = 0; i < 3; i++)
    {
        drawCell(x + (length * i), y, length);
    }

    for (i = 0; i < 3; i++)
    {
        drawCell(x + (length * i), y + ((length / 2)), length);
    }

    for (i = 0; i < 3; i++)
    {
        drawCell(x + (length * i), y + ((length / 2) * 2), length);
    }

    // drawCell(x, y, length);
    // drawCell(x + length, y, length);
}

int main()
{

    int i;
    char gameboard[3][3] = {
        {'n', 'n', 'n'},
        {'n', 'n', 'n'},
        {'n', 'n', 'n'}};

    clrscr();
    window(5, 5, 1000, 1000);

    drawGameboard(25, 5, 10);
    // drawOnScreen(1, 1);

    getch();
}