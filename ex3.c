#include <stdio.h>

#ifndef ROWS
#define ROWS 6
#endif

#ifndef COLS
#define COLS 7
#endif

#define CONNECT_N 4

/* Tokens */
#define EMPTY '.'
#define TOKEN_P1 'X'
#define TOKEN_P2 'O'

#define HUMAN 1
#define COMPUTER 2

void initBoard(char board[][COLS], int rows, int cols);

void printBoard(char board[][COLS], int rows, int cols) {
    printf("\n");
    for (int r = 0; r < rows; r++) {
        printf("|");
        for (int c = 0; c < cols; c++) {
            putchar(board[r][c]);
            printf("|");
        }
        printf("\n");
    }
    for (int c = 1; c <= cols; c++) {
        printf(" %d", c % 10);
    }
    printf("\n\n");
}

int getPlayerType(int playerNumber) {
    char ch;
    while (1) {
        printf("Choose type for player %d: h - human, c - computer: ", playerNumber);
        int n = scanf(" %c", &ch);
        if (n != 1) {
            printf("Input error. Try again.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        if (ch == 'h' || ch == 'H') return HUMAN;
        if (ch == 'c' || ch == 'C') return COMPUTER;

        printf("Invalid selection. Enter h or c.\n");
        while (getchar() != '\n'); // clear rest of input
    }
}

int isColumnFull(char board[][COLS], int rows, int cols, int col);

int isBoardFull(char board[][COLS], int rows, int cols);

int isInBounds(int rows, int cols, int r, int c);

/* Return index of row where token will land, or -1 if column full */
int getFreeRow(char board[][COLS], int rows, int cols, int col);

/* Place token in column (0-based). Return row index or -1 if illegal */
int makeMove(char board[][COLS], int rows, int cols, int col, char token);

int checkVictory(char board[][COLS], int rows, int cols, int r, int c, char token);

/* Human player: asks repeatedly until a valid non-full column is chosen (0-based) */
int humanChoose(char board[][COLS], int rows, int cols);


/* Computer*/
int computerChoose(char board[][COLS], int rows, int cols, char mytoken, char optoken);

void runConnectFour(char board[][COLS], int rows, int cols, int p1Type, int p2Type);

int main() {
    char board[ROWS][COLS];
    printf("Connect Four (%d rows x %d cols)\n\n", ROWS, COLS);
    int p1Type = getPlayerType(1);
    int p2Type = getPlayerType(2);
    initBoard(board, ROWS, COLS);
    printBoard(board, ROWS, COLS);
    runConnectFour(board, ROWS, COLS, p1Type, p2Type);
    return 0;
}
