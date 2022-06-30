#define SIZE 3
#define BOARDLINESEPERATORSIZE (4 * (SIZE - 1) + 1)

#define X -1
#define O 1
#define BLANK 0

#define PLAYERTURN O

#define GAMEISRUNNING 0
#define DRAW 10

typedef struct {
    int x;
    int y;
    int eval;
} Move;

int g_board[3][3];
int g_currentTurn = O;

void InitBoard();
void PrintBoard();
void PrintBoardSymbolsFromLine(int y);
void PrintSymbol(int integer);
void PrintBoardLineSeperator();

Move GetBestMove();
int EvalateGameStatus(int status);

Move AskForMove();
int IsBetweenBoardRange(int integer);
int IsMoveValid(Move *move);
void MakeMove(Move Move);
void UnMakeMove(Move move);
int GetGameStatus();
int GetGameStatusForRows();
int GetGameStatusForColumns();
int GetGameStatusForZigZags();
int isGameStatusDraw();

void ChangeTurn();
void PrintEndGameMessage(int status);

