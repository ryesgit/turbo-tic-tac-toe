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

typedef struct
{
    char marker;
    int playerNumber;
} Player;

void typeOnScreen(message, x, y)
{
    g(x, y);
    p("%s", message);
}

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

void playTurn(Player currentPlayer, char gameboard[3][3])
{
    int choice, row, column;
    typeOnScreen("Please type in a choice: ", 25, 25);
    p("");
    s("%i", &choice);

    if (choice <= 3)
    {
        row = 0;
    }
    else if (choice > 3 && choice <= 6)
    {
        row = 1;
    }
    else
    {
        row = 2;
    }

    column = (choice - 1) % 3;

    gameboard[row][column] = currentPlayer.marker;
}

void drawGameboard(int x, int y, int length, char gameboard[3][3])
{
    int i;

    clrscr();

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
}

int main()
{
    int i, j;

    Player playerOne = {
        'x',
        1};

    Player playerTwo = {
        'o',
        2};

    Player currentPlayer = playerOne;

    char gameboard[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}};

    drawGameboard(25, 5, 10, gameboard);

    playTurn(currentPlayer, gameboard);

    drawGameboard(25, 5, 10, gameboard);

    getch();

    return 0;
}