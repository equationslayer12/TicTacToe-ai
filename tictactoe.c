
#include <stdio.h>

#define SIZE 3
#define X -1
#define O 1
#define BLANK 0

typedef struct {
    int x;
    int y;
} Move;

void InitBoard();
void PrintBoard();
void PrintBoardSymbolsFromLine(int y);
void PrintSymbol(int integer);
void PrintBoardLineSeperator();

Move AskForMove();
int IsBetweenBoardRange(int integer);
int IsMoveValid(Move *move);
void MakeMove(Move Move);
void ChangeTurn();

int g_board[3][3];
int g_currentTurn = O;

int BOARDLINESEPERATORSIZE = 4 * (SIZE - 1) + 1;

int main(int argc, char const *argv[])
{
    InitBoard();

    int gameIsRunning = 1;
    while (gameIsRunning) {
        Move move = AskForMove();
        MakeMove(move);
        ChangeTurn();
    }

    return 0;
}

void InitBoard() {
    // fill the board with blank symbols
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            g_board[y][x] = BLANK;
        }
    }
}

void PrintBoard() { 
    for (int y = 0; y < SIZE; y++) {
        PrintBoardSymbolsFromLine(y);

        if (y != SIZE - 1) {
            PrintBoardLineSeperator();
        }

        printf("\n");
    }
}

void PrintBoardSymbolsFromLine(int y) {
    for (int x = 0; x < SIZE; x++) {
        PrintSymbol(g_board[y][x]);
        if (x != SIZE - 1) {
            printf(" | ");
        }
        else {
            /* if we got to the last element in the line, print a newline */
            printf("\n");
        }
    }
}

void PrintSymbol(int integer) {
    switch (integer)
    {
        case X:
            printf("X");
            break;
        case O:
            printf("O");
            break;
        case BLANK:
            printf(" ");
            break;
    }
}

void PrintBoardLineSeperator() {
    for (size_t i = 0; i < BOARDLINESEPERATORSIZE; i++) {
        printf("-");
    }
}

Move AskForMove() {
    PrintBoard();
    printf("\nCurrent turn: ");
    PrintSymbol(g_currentTurn);
    printf("\n");

    Move new_move = {-1, -1};
    while (1) {
        while (!IsBetweenBoardRange(new_move.y)) {
            printf("Input Row (1-%d):\n", SIZE);
            scanf("%d", &new_move.y);
            new_move.y--;
        }

        while (!IsBetweenBoardRange(new_move.x)) {
            printf("Input Column (1-%d):\n", SIZE);
            scanf("%d", &new_move.x);
            new_move.x--;
        }

        if (!IsMoveValid(&new_move)) {
            printf("Invalid move!\n");
            new_move.x = -1;
            new_move.y = -1;
            continue;
        }
        else {
            break;
        }
    }
    return new_move;
}

int IsBetweenBoardRange(int integer) {
    return 0 <= integer && integer < SIZE;
}

int IsMoveValid(Move *move) {
    if (!IsBetweenBoardRange(move -> y)) {
        return 0;
    }
    return g_board[move -> y][move -> x] == BLANK;
}

void MakeMove(Move move) {
    g_board[move.y][move.x] = g_currentTurn;
}

void ChangeTurn() {
    if (g_currentTurn == O) {
        g_currentTurn = X;
    }
    else {
        g_currentTurn = O;
    }
}



