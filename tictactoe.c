
#include <stdio.h>
#include "tictactoe.h"


int main(int argc, char const *argv[])
{
    InitBoard();

    int status = GAMEISRUNNING;
    while (status == GAMEISRUNNING) {
        Move move;
        if (g_currentTurn == PLAYERTURN) {
            move = AskForMove();
        }
        else {
            move = GetBestMove();
        }

        MakeMove(move);
        status = GetGameStatus();
        ChangeTurn();
    }
    
    PrintEndGameMessage(status);
    return 0;
}

/* minmax! */
Move GetBestMove() {

    int status = GetGameStatus();
    if (status != GAMEISRUNNING) {
        return (Move) {0, 0, EvalateGameStatus(status)};

    }
    
    Move bestMove = {0, 0, -10000};

    // loop through each one of the empty moves
    for (size_t y = 0; y < SIZE; y++) {
        for (size_t x = 0; x < SIZE; x++) {
            if (g_board[y][x] == BLANK) {
                Move move = {x, y, 0};

                MakeMove(move);
                ChangeTurn();
                move.eval = -(GetBestMove().eval);   // that negative sign is very important
                UnMakeMove(move);
                ChangeTurn();

                if (move.eval > bestMove.eval) {
                    bestMove = move;
                }
            }
        }
    }
    return bestMove;
}

int EvalateGameStatus(int status) {
    if (status == GAMEISRUNNING)
        return 0;
    if (status == DRAW)
        return -1;
    if (status == g_currentTurn)
        return 10;
    else
        return -10;
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

void UnMakeMove(Move move) {
    g_board[move.y][move.x] = BLANK;
}

int GetGameStatus() {
    int status;

    status = GetGameStatusForRows();
    if (status != GAMEISRUNNING) {
        return status;
    }

    status = GetGameStatusForColumns();
    if (status != GAMEISRUNNING) {
        return status;
    }

    status = GetGameStatusForZigZags();
    if (status != GAMEISRUNNING) {
        return status;
    }

    if (isGameStatusDraw()) {
        return DRAW;
    }

    return GAMEISRUNNING;
};

int GetGameStatusForRows() {
    for (size_t y = 0; y < SIZE; y++) {
        int lastElement = g_board[y][0];
        for (size_t x = 0; x < SIZE; x++) {
            if (lastElement != g_board[y][x] || g_board[y][x] == BLANK) {
                break;
            }
            lastElement = g_board[y][x];

            if (x == SIZE - 1) {
                return g_board[y][x];
            }
        }
    }
    return GAMEISRUNNING;
}

int GetGameStatusForColumns() {
    for (size_t x = 0; x < SIZE; x++) {
        int lastElement = g_board[0][x];
        for (size_t y = 0; y < SIZE; y++) {
            if (lastElement != g_board[y][x] || g_board[y][x] == BLANK) {
                break;
            }
            lastElement = g_board[y][x];

            if (y == SIZE - 1) {
                return g_board[y][x];
            }
        }
    }
    return GAMEISRUNNING;
}

int GetGameStatusForZigZags() {

    // check for \
    //
    int lastElement = g_board[0][0];
    int x = 1, y = 1;
    for (; y < SIZE; y++, x++) {
        if (lastElement != g_board[y][x] || g_board[y][x] == BLANK) {
            break;
        }
        if (y == SIZE - 1) {
            return g_board[y][x];
        }
    }
    
    // check for /
    // 
    lastElement = g_board[0][SIZE-1];
    x = SIZE - 1, y = 0;
    for (; y < SIZE; y++, x--) {
        if (lastElement != g_board[y][x] || g_board[y][x] == BLANK) {
            break;
        }
        if (y == SIZE - 1) {
            return g_board[y][x];
        }
    }

    return GAMEISRUNNING;
}

int isGameStatusDraw() {
    for (size_t y = 0; y < SIZE; y++) {
        for (size_t x = 0; x < SIZE; x++) {
            if (g_board[y][x] == BLANK) {
                return 0;
            }
        }
    }
    return 1;
}

void ChangeTurn() {
    if (g_currentTurn == O) {
        g_currentTurn = X;
    }
    else {
        g_currentTurn = O;
    }
}

void PrintEndGameMessage(int status) {
    PrintBoard();
    printf("GG!\n");
    if (status == DRAW) {
        printf("Draw!");
    }
    else {
        PrintSymbol(status);
        printf(" won!");
    }
}


