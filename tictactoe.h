#define SIZE 3
#define BOARDLINESEPERATORSIZE (4 * (SIZE - 1) + 1)

#define X -1
#define O 1
#define BLANK 0

#define GAMEISRUNNING 0
#define DRAW 10

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
int GetGameStatus();
int GetGameStatusForRows();
int GetGameStatusForColumns();

void ChangeTurn();
void PrintEndGameMessage(int status);

int g_board[3][3];
int g_currentTurn = O;