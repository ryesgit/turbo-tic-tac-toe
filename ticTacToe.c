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

int hasHorizontalWinner(char gameboard[3][3])
{

    int i;

    int hasWinner = 0;

    for (i = 0; i < 3; i++)
    {
        if (gameboard[i][0] == gameboard[i][1] && gameboard[i][1] == gameboard[i][2])
        {
            hasWinner = 1;
            return hasWinner;
        }
    }

    return hasWinner;
}

int hasVerticalWinner(char gameboard[3][3])
{

    int i;
    int j = 0;

    int hasWinner = 0;

    for (i = 0; i < 3; i++)
    {
        if (gameboard[j][i] == gameboard[j + 1][i] && gameboard[j + 1][i] == gameboard[j + 2][i])
        {
            hasWinner = 1;
            return hasWinner;
        }
    }

    return hasWinner;
}

int hasDiagonalWinner(char gameboard[3][3])
{

    int hasWinner = 0;

    if (gameboard[0][0] == gameboard[1][1] && gameboard[1][1] == gameboard[2][2] ||
        gameboard[0][2] == gameboard[1][1] && gameboard[1][1] == gameboard[2][0])
    {
        hasWinner = 1;
        return hasWinner;
    }

    return hasWinner;
}

int hasWinner(char gameboard[3][3])
{

    if (hasHorizontalWinner(gameboard) || hasVerticalWinner(gameboard) || hasDiagonalWinner(gameboard))
    {
        return 1;
    }

    // char diagonalWinningPatterns[2][3] = {
    //     {gameboard[0][0], gameboard[1][1], gameboard[2][2]},
    //     {gameboard[0][2], gameboard[1][1], gameboard[2][0]}};
    return 0;
}

int hasDraw(char gameboard[3][3])
{
    int i, j;

    int filledCells = 0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (gameboard[i][j] == 'x' || gameboard[i][j] == 'o')
            {
                filledCells++;
            }
        }
    }
    if (filledCells >= 9 && hasWinner(gameboard) != 1)
    {
        return 1;
    }

    return 0;
}

void playTurn(Player currentPlayer, char gameboard[3][3])
{
    int illegalMove;
    illegalMove = 1;
    while (illegalMove)
    {
        int choice, row, column;
        typeOnScreen("Please type in a choice: ", 25, 25);

        p("");
        s("%i", &choice);

        if (!isdigit(choice))
        {
            clrscr();
            p("Please enter a number only");
            delay(5000);
        }

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

        if (gameboard[row][column] == 'x' || gameboard[row][column] == 'o')
        {
            g(25, 25);
            p("Illegal move, try again");
            delay(1000);
            continue;
        }
        else
        {
            p("%c", gameboard[row][column]);
            gameboard[row][column] = currentPlayer.marker;
            illegalMove = 0;
        }
    }
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

void ticTacToe()
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

    // While there is no winner and there is no draw, just play game
    while (hasWinner(gameboard) != 1 && hasDraw(gameboard) != 1)
    {
        if (currentPlayer.playerNumber == playerOne.playerNumber)
        {
            currentPlayer = playerTwo;
        }
        else
        {
            currentPlayer = playerOne;
        }
        playTurn(currentPlayer, gameboard);
        drawGameboard(25, 5, 10, gameboard);
    }

    g(17, 13);

    if (hasWinner(gameboard) == 1)
    {
        p("Congratulations, player number %i! You have won!", currentPlayer.playerNumber);
    }

    if (hasDraw(gameboard) == 1)
    {
        p("It's a draw!");
    }
    g(25, 10);

    promptBeforeExit();
}